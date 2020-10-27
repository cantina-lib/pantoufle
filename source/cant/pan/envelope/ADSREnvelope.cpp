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
            const adsr::ArrayVelocityRatios &ratios
            )
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(numberVoices, lengths, ratios));
    }

    ADSREnvelope::
    ADSREnvelope(
            const size_u numberVoices,
            const adsr::ArrayLengths& lengths,
            const adsr::ArrayVelocityRatios& ratios
            )
        : m_lengths(lengths),
        m_ratios(ratios),
        m_speeds(computeSpeeds(m_lengths, ratios)),
        m_states(numberVoices)
    {
        checkLengths(m_lengths);

        m_timeListener = std::make_shared<patterns::SelfEventListener<ADSREnvelope, time_d>>(
            this,
            &ADSREnvelope::onTimeUpdateDelta
            );
        m_tickListener = std::make_shared<patterns::SelfEventListener<ADSREnvelope, void*>>(
          this,
          &ADSREnvelope::onTimerTick
      );
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
            = (ratios.at(ADSRState::eAttack) - ratios.at(ADSRState::eSustain))
                    / lengths.at(ADSRState::eDecay);
        speeds.at(ADSRState::eRelease) = ratios.at(ADSRState::eSustain) / lengths.at(ADSRState::eRelease);
        return speeds;
    }

    void
    ADSREnvelope::onTimeUpdateDelta(time_d tDelta)
    {
        // update type and length of states
        for (auto& state : m_states)
        {
            state.updateTypeLength(this, tDelta);
        }
        // update the simulation with regards to the changes
        // the simulation will itself update the velocity ratio.
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
        state.updateTypeLengthManual(this, note);
        state.apply(note);
        if (!note.getVoice())
        {
            std::cout << "target: " << state.m_target->getPosition().get<0>() << "| ratio: " << state.getVelocityRatio() << std::endl;
        }
    }

    void
    ADSREnvelope::
    subscribe(UPtr<MidiTimer>& timer)
    {
      timer->addOnTimeUpdateCurrentListener(m_timeListener);
      timer->addOnTickListener(m_tickListener);
    }

    void
    ADSREnvelope::
    unsubscribe(UPtr<MidiTimer>& timer)
    {
      timer->removeOnTimeUpdateCurrentListener(m_timeListener);
      timer->removeOnTickListener(m_tickListener);
    }

    void ADSREnvelope::onTimerTick(void *)
    {
      for(auto& state : m_states)
      {
        state.onTimerTick(nullptr);
      }
    }

    CANTINA_PAN_NAMESPACE_END
