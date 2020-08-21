//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    UPtr<VelocityEnvelope>
    ADSREnvelope::
    make(
            const size_m numberVoices,
            const ADSRState::ArrayLengths &lengths,
            const ADSRState::ArrayVelocityRatios &velocities
            )
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(numberVoices, lengths, velocities));
    }

    ADSREnvelope::
    ADSREnvelope(
            const size_m numberVoices,
            const ADSRState::ArrayLengths& lengths,
            const ADSRState::ArrayVelocityRatios& velocities
            )

    : VelocityEnvelope(numberVoices),
    _lengths(lengths),
     _velocityRatios(velocities),
    _states(numberVoices)
    {
        checkLengths(lengths);
        setCallbacks();
    }

    void
    ADSREnvelope::
    checkLengths(const ADSRState::ArrayLengths &lengths)
    {
        if (
                (lengths.at(ADSRState::eAttack) < static_cast<time_m>(0.))
                ||(lengths.at(ADSRState::eDecay) < static_cast<time_m>(0.))
                || (lengths.at(ADSRState::eRelease) < static_cast<time_m>(0.))
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
        _callbacks.at(ADSRState::eAttack) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / _lengths.at(ADSRState::eAttack),
                            static_cast<float_m>(0),
                            _velocityRatios.at(ADSRState::eAttack)
                            );
                };
        _callbacks.at(ADSRState::eDecay) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / _lengths.at(ADSRState::eDecay),
                            _velocityRatios.at(ADSRState::eAttack),
                            _velocityRatios.at(ADSRState::eSustain)
                            );
                };
        _callbacks.at(ADSRState::eSustain) =
                [this](const time_m t) -> float_m
                {
                    return _velocityRatios.at(ADSRState::eSustain);
                };
        _callbacks.at(ADSRState::eRelease) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / _lengths.at(ADSRState::eRelease),
                            _velocityRatios.at(ADSRState::eSustain),
                            static_cast<float_m>(0.)
                            );
                };
    }

    void ADSREnvelope::
    flushChange()
    {
        for (auto& state : _states)
        {
            state.flushChange();
        }
    }

    ADSRState::
    ADSRState()
    : _type(ADSRStateType::eNotPlaying),
      _tStart(),
      _flagChangedPlaying(false)
    {

    }


    bool
    ADSRState::
    isSustainFinite(const ArrayLengths& lengths)
    {
        return lengths.at(ADSRStateType::eSustain) >= static_cast<time_m>(0.);
    }


    time_m
    ADSRState::
    getLength(const time_m tCurrent) const
    {
        return tCurrent - _tStart;
    }

    time_m
    ADSRState::
    computeTimeStart(const time_m tCurrent, const time_m length)
    {
        return tCurrent - length;
    }

    void
    ADSRState::
    set(const ADSRStateType type, const time_m tStart)
    {
        if (type != _type)
        {
            raiseFlagChanged();
        }
        _type = type;
        _tStart = tStart;
    }

    void
    ADSRState::
    setFromLength(const time_m tCurrent, const ADSRStateType type, const time_m length)
    {
        set(type, computeTimeStart(tCurrent, length));
    }

    void
    ADSRState::
    update(const time_m tCurrent, const MidiNoteInternal &note, const ArrayLengths& lengths)
    {
        if (note.justChangedPlaying())
        {
            if (note.isPlaying())
            {
                set(ADSRStateType::eAttack, tCurrent);
            }
            else
            {
                set(ADSRStateType::eRelease, tCurrent);
            }
        }
        else
        {
            compute(tCurrent, lengths);
        }
    }

    void
    ADSRState::
    apply(const time_m tCurrent, MidiNoteInternal &note, const ArrayCallbacks& callbacks) const
    {
        const float_m velocityRatio = getVelocityRatio(tCurrent, callbacks);
        note.setVelocity(note.getVelocity() * velocityRatio);
        note.setPlaying(this->isPlaying());
        note.setChangedPlaying(this->justChangedPlaying());
    }

    void
    ADSRState::
    flushChange()
    {
        discardFlagChanged();
    }

    bool
    ADSRState::
    isPlaying() const
    {
        return _type != ADSRStateType::eNotPlaying;
    }

    bool
    ADSRState::
    justChangedPlaying() const
    {
        return _flagChangedPlaying;
    }

    void
    ADSRState::
    raiseFlagChanged()
    {
        _flagChangedPlaying = true;
    }

    void
    ADSRState::
    discardFlagChanged()
    {
        _flagChangedPlaying = false;
    }

    void
    ADSRState::
    compute(const time_m tCurrent, const ArrayLengths& lengths)
    {
        ADSRStateType type = _type;
        time_m length = getLength(tCurrent);
        /* starting values */
        ADSRState::REC_compute(type, length, lengths);
        setFromLength(tCurrent, type, length);
    }

    void
    ADSRState::
    REC_compute(ADSRStateType& type, time_m& length, const ArrayLengths& lengths)
    {
        switch (type)
        {
            case ADSRStateType::eAttack:
                if (length > lengths.at(eAttack))
                {
                    /* */
                    type = ADSRStateType::eDecay;
                    length -= lengths.at(eAttack);
                    break;
                }
                return;
            case ADSRStateType::eDecay:
                if (length > lengths.at(eDecay))
                {
                    type = ADSRStateType::eSustain;
                    length -= lengths.at(eDecay);
                    break;
                }
                return;
            case ADSRStateType::eSustain:
                if (isSustainFinite(lengths) && (length > lengths.at(eSustain)))
                {
                    type = ADSRStateType::eRelease;
                    length -= lengths.at(eSustain);
                    break;
                }
                return;
            case ADSRStateType::eRelease:
                if (length > lengths.at(eRelease))
                {
                    type = ADSRStateType::eNotPlaying;
                    length -= lengths.at(eRelease);
                    break;
                }
                return;
            case ADSRStateType::eNotPlaying:
                /* nothing to do */
                return;
        }
        REC_compute(type, length, lengths);
    }

    float_m
    ADSRState::
    getVelocityRatio(const time_m tCurrent, const ArrayCallbacks& callbacks) const
    {
        if (!isPlaying())
        {
            return static_cast<float_m>(0);
        }
        return callbacks.at(_type)(getLength(tCurrent));
    }


    void
    ADSREnvelope::
    process(MidiNoteInternal &note)
    {
        /*
         * There used to be a concept of 'extendability'
         * where a note could be extended by the envelope or not
         * now assuming every note is extendable.
         * You'd need to add a _isExtendable field to MidiNoteInternal
         * to go back.
         */
        ADSRState& state = _states.at(note.getVoice());
        const time_m tCurrent = getCurrentTime();
        state.update(tCurrent, note, _lengths);
        state.apply(tCurrent, note, _callbacks);
    }
}

