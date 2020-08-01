//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <sstream>
#include <fmt/format.h>

namespace cant::pan
{
    UPtr<VelocityEnvelope>
    ADSREnvelope::
    make(const ADSREnvelope::ArrayLength &lengths, const ADSREnvelope::ArrayVelocityRatios &velocities)
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(lengths, velocities));
    }

    ADSREnvelope::
    ADSREnvelope(const ArrayLength& lengths, const ArrayVelocityRatios& velocities)
    : VelocityEnvelope(),
    _lengths(lengths),
      _velocityRatios(velocities)
    {
        checkLengths(lengths);
        setCallbacks();
    }

    void
    ADSREnvelope::
    checkLengths(const ArrayLength &lengths)
    {
        if (
                (lengths.at(eAttack) < static_cast<time_m>(0.))
                ||(lengths.at(eDecay) < static_cast<time_m>(0.))
                || (lengths.at(eRelease) < static_cast<time_m>(0.))
                )
        {
            /* todo: better message */
            throw PANTOUFLE_EXCEPTION("ADSR length invalid, is negative but not sustain.");
        }
    }

    vel_m
    ADSREnvelope::
    getBarycentre(const time_m lambda, const vel_m v1, const vel_m v2)
    {
        if(lambda > static_cast<time_m>(1.) || lambda < static_cast<time_m>(0.))
        {
            throw PANTOUFLE_EXCEPTION("Lambda out of range.");
        }
        return (static_cast<time_m>(1.) - lambda) * v1 + lambda * v2;
    }

    void
    ADSREnvelope::
    setCallbacks()
    {
        _callbacks.at(eAttack) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eAttack), static_cast<float_m>(0), _velocityRatios.at(eAttack));
                };
        _callbacks.at(eDecay) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eDecay), _velocityRatios.at(eAttack), _velocityRatios.at(eSustain));
                };
        _callbacks.at(eSustain) =
                [this](const time_m t) -> float_m
                {
                    return _velocityRatios.at(eSustain);
                };
        _callbacks.at(eRelease) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eRelease), _velocityRatios.at(eSustain), static_cast<float_m>(0.));
                };
    }


    bool
    ADSREnvelope::
    isSustainFinite() const
    {
        return _lengths.at(eSustain) >= static_cast<time_m>(0.);
    }

    bool
    ADSREnvelope::
    isPlayingState(ADSRState state)
    {
        return state != ADSRState::eNotPlaying;
    }

    void
    ADSREnvelope::
    computeState(ADSRState &state, time_m &stateLength, const time_m noteLength) const
    {
        /* starting values */
        state = ADSRState::eAttack;
        stateLength = noteLength;

        REC_computeState(state, stateLength);
    }

    void
    ADSREnvelope::
    REC_computeState(ADSRState& state, time_m& length) const
    {
        switch (state)
        {
            case ADSRState::eAttack:
                if (length > _lengths.at(eAttack))
                {
                    /* */
                    state = ADSRState::eDecay;
                    length -= _lengths.at(eAttack);
                    break;
                }
                return;
            case ADSRState::eDecay:
                if (length > _lengths.at(eDecay))
                {
                    state = ADSRState::eSustain;
                    length -= _lengths.at(eDecay);
                    break;
                }
                return;
            case ADSRState::eSustain:
                if (isSustainFinite() && (length > _lengths.at(eSustain)))
                {
                    state = ADSRState::eRelease;
                    length -= _lengths.at(eSustain);
                    break;
                }
                return;
            case ADSRState::eRelease:
                if (length > _lengths.at(eRelease))
                {
                    state = ADSRState::eNotPlaying;
                    length -= _lengths.at(eRelease);
                    break;
                }
                return;
            case ADSRState::eNotPlaying:
                /* nothing to do */
                return;
        }
        REC_computeState(state, length);
    }

    void
    ADSREnvelope::
    updateNote(MidiNoteInternal &note, const ADSRState state, const time_m stateLength) const
    {
        /*
         * There used to be a concept of 'extendability'
         * where a note could be extended by the envelope or not
         * now assuming every note is extendable.
         * You'd need to add a _isExtendable field to MidiNoteInternal
         * to go back.
         */
        const bool stateIsPlaying = isPlayingState(state);
        const bool hasStateChangedNote = stateIsPlaying != note.isPlaying();
        note.setPlaying(note.isPlaying() || stateIsPlaying);
        if (note.justChanged())
        {
            note.setChanged(!stateIsPlaying);
        }
        else
        {
            note.setChanged(hasStateChangedNote);
        }
    }

    float_m
    ADSREnvelope::
    computeVelocityRatio(const ADSRState state, const time_m stateLength) const
    {
        if (!isPlayingState(state))
        {
            return static_cast<float_m>(0);
        }
        return _callbacks.at(state)(stateLength);
    }


    void
    ADSREnvelope::
    apply(time_m tCurrent, MidiNoteInternal &note) const
    {
        ADSRState state;
        time_m stateLength;
        // naïve state, taking only time into account.
        computeState(state, stateLength, note.getLength(tCurrent));
        updateNote(note, state, stateLength);

        const float_m velocityRatio = computeVelocityRatio(state, stateLength);
        note.setVelocity(note.getVelocity() * velocityRatio);
    }
}

