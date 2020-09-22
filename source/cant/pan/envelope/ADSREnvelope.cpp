//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>
#include <cant/pan/envelope/ADSRState.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    UPtr<VelocityEnvelope>
    ADSREnvelope::
    make(
            const size_u numberVoices,
            const adsr::ArrayLengths &lengths,
            const adsr::ArrayVelocityRatios &velocities
            )
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(numberVoices, lengths, velocities));
    }

    ADSREnvelope::
    ADSREnvelope(
            const size_u numberVoices,
            const adsr::ArrayLengths& lengths,
            const adsr::ArrayVelocityRatios& velocities
            )

    : m_lengths(lengths),
      m_velocityRatios(velocities),
      m_speeds(computeSpeeds(m_lengths, m_velocityRatios)),
      m_states(numberVoices)
    {
        checkLengths(m_lengths);
    }

    void
    ADSREnvelope::
    checkLengths(const adsr::ArrayLengths &lengths)
    {
        if (
                (lengths.at(ADSRState::eAttack) < static_cast<time_d>(0.))
                ||(lengths.at(ADSRState::eDecay) < static_cast<time_d>(0.))
                || (lengths.at(ADSRState::eRelease) < static_cast<time_d>(0.))
                )
        {
            /* todo: better message */
            throw PANTOUFLE_EXCEPTION("NOooo");
        }
    }


    bool
    ADSREnvelope::
    isSustainFinite(const adsr::ArrayLengths& lengths)
    {
        return lengths.at(ADSRState::ADSRStateType::eSustain) >= static_cast<time_d>(0.);
    }

    adsr::ArraySpeeds
    ADSREnvelope::
    computeSpeeds(const adsr::ArrayLengths &lengths, const adsr::ArrayVelocityRatios &ratios)
    {
        adsr::ArraySpeeds speeds;
        speeds.at(ADSRState::eAttack) = ratios.at(ADSRState::eAttack) / lengths.at(ADSRState::eAttack);
        speeds.at(ADSRState::eDecay)
            = std::abs(ratios.at(ADSRState::eAttack) - ratios.at(ADSRState::eSustain))
                    / lengths.at(ADSRState::eDecay);
        speeds.at(ADSRState::eRelease) = ratios.at(ADSRState::eSustain) / lengths.at(ADSRState::eRelease);
        return speeds;
    }

    void
    ADSREnvelope::
    updateDelta(time_d tDelta)
    {
        for (auto& state : m_states)
        {
            state.update(this, tDelta);
        }
    }

    void
    ADSREnvelope::
    process(MidiNoteInternal &note)
    {
        /*
         * There used to be a concept of 'extendability'
         * where a note could be extended by the envelope or not
         * now assuming every note is extendable.
         */
        ADSRState& state = m_states.at(note.getVoice());
        state.update(this, note);
        state.apply(note);
    }

    void
    ADSREnvelope::
    subscribe(event::Ptr<MidiTimer> timer)
    {
        for (auto& state : m_states)
        {
            state.subscribe(timer->changeFlagModule.get());
        }
    }

    void
    ADSREnvelope::
    unsubscribe(event::Ptr<MidiTimer> timer)
    {
        for (auto& state : m_states)
        {
            state.unsubscribe(timer->changeFlagModule.get());
        }
    }



CANTINA_PAN_NAMESPACE_END
