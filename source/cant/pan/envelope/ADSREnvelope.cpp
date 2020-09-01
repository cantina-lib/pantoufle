//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <cant/pan/common/PantoufleException.hpp>

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
      m_lengths(lengths),
      m_velocityRatios(velocities),
      m_states(numberVoices)
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
        m_callbacks.at(ADSRState::eAttack) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / m_lengths.at(ADSRState::eAttack),
                            static_cast<float_m>(0),
                            m_velocityRatios.at(ADSRState::eAttack)
                            );
                };
        m_callbacks.at(ADSRState::eDecay) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / m_lengths.at(ADSRState::eDecay),
                            m_velocityRatios.at(ADSRState::eAttack),
                            m_velocityRatios.at(ADSRState::eSustain)
                            );
                };
        m_callbacks.at(ADSRState::eSustain) =
                [this](const time_m t) -> float_m
                {
                    return m_velocityRatios.at(ADSRState::eSustain);
                };
        m_callbacks.at(ADSRState::eRelease) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(
                            t / m_lengths.at(ADSRState::eRelease),
                            m_velocityRatios.at(ADSRState::eSustain),
                            static_cast<float_m>(0.)
                            );
                };
    }

    void ADSREnvelope::
    flushChange()
    {
        for (auto& state : m_states)
        {
            state.flushChange();
        }
    }

    ADSRState::
    ADSRState()
    : m_type(ADSRStateType::eNotPlaying),
      m_tStart(),
      m_flagChangePlaying(false)
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
        return tCurrent - m_tStart;
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
        if (type != m_type)
        {
            raiseFlagChanged();
        }
        m_type = type;
        m_tStart = tStart;
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
        return m_type != ADSRStateType::eNotPlaying;
    }

    bool
    ADSRState::
    justChangedPlaying() const
    {
        return m_flagChangePlaying;
    }

    void
    ADSRState::
    raiseFlagChanged()
    {
        m_flagChangePlaying = true;
    }

    void
    ADSRState::
    discardFlagChanged()
    {
        m_flagChangePlaying = false;
    }

    void
    ADSRState::
    compute(const time_m tCurrent, const ArrayLengths& lengths)
    {
        ADSRStateType type = m_type;
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
        return callbacks.at(m_type)(getLength(tCurrent));
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
        ADSRState& state = m_states.at(note.getVoice());
        const time_m tCurrent = getCurrentTime();
        state.update(tCurrent, note, m_lengths);
        state.apply(tCurrent, note, m_callbacks);
    }
}

