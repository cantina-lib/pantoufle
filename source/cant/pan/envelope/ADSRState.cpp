//
// Created by binabik on 22/09/2020.
//

#include <cant/pan/envelope/ADSRState.hpp>
#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/maths/utils.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    ADSRState::
    ADSRState()
            : m_type(ADSRStateType::eNotPlaying),
              m_length(),
              m_oscillator(std::make_unique<VelocityOscillator>()),
              m_changeFlagModule(std::make_unique<ChangeFlagUpdateModule>())
    { }

    void
    ADSRState::
    computeVelocityRatio(time_d tDelta)
    {

        //
        m_oscillator->stepDelta(tDelta);
        //
    }


    void
    ADSRState::
    update(const ADSREnvelope *env, const MidiNoteInternal &note)
    {
        if (note.justChangedPlaying())
        {
            if (note.isPlaying())
            {
                setTypeLengthManual(env, ADSRStateType::eAttack);
            }
            else
            {
                setTypeLengthManual(env, ADSRStateType::eRelease);
            }
        }
    }

    void
    ADSRState::
    compute(const ADSREnvelope *env, time_d tDelta)
    {
        // starting values.
        ADSRStateType type = m_type;
        time_d length = getLength() + tDelta;

        // recursively computing updated type and length.
        computeTypeLengthRecursive(type, length, env->m_lengths);
        setTypeLength(env, type, length);
        // velocity ratio is subject to change, update it.
        computeVelocityRatio(tDelta);
    }

    void
    ADSRState::
    setTypeLength(const ADSREnvelope *env, ADSRStateType type, time_d length)
    {
        m_length = length;
        const ADSRStateType previousType = getType();
        setType(type);
        const bool typeChanged = getType() != previousType;
        if (typeChanged)
        {
            const type_d targetSpeed = getTypeTargetSpeed(env->m_speeds);
            const type_d targetRatio = getTypeTargetVelocityRatio(env->m_velocityRatios);
            m_oscillator->setPull(targetSpeed);
            m_oscillator->setTarget(targetRatio);
        }
    }

    void
    ADSRState::
    computeTypeLengthRecursive(ADSRStateType& type, time_d& length, const adsr::ArrayLengths& lengths)
    {
        switch (type)
        {
            case ADSRStateType::eAttack:
                if (length >= lengths.at(eAttack))
                {
                    type = ADSRStateType::eDecay;
                    length -= lengths.at(eAttack);
                    break;
                }
                return;
            case ADSRStateType::eDecay:
                if (length >= lengths.at(eDecay))
                {
                    type = ADSRStateType::eSustain;
                    length -= lengths.at(eDecay);
                    break;
                }
                return;
            case ADSRStateType::eSustain:
                if (ADSREnvelope::isSustainFinite(lengths) && (length > lengths.at(eSustain)))
                {
                    type = ADSRStateType::eRelease;
                    length -= lengths.at(eSustain);
                    break;
                }
                return;
            case ADSRStateType::eRelease:
                if (length >= lengths.at(eRelease))
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
        computeTypeLengthRecursive(type, length, lengths);
    }

    void
    ADSRState::
    apply(MidiNoteInternal &note) const
    {
        const type_d velocityRatio = getVelocityRatio();
        note.setVelocity(note.getVelocity() * velocityRatio);
        note.setPlaying(this->isPlaying());
        note.setChangedPlaying(this->justChangedPlaying());
    }


    type_d
    ADSRState::
    getTypeTargetVelocityRatio(const adsr::ArrayVelocityRatios &ratios) const
    {
        auto ratio = static_cast<type_d>(0.);
        switch (getType())
        {
            case ADSRStateType::eAttack     : ratio = ratios.at(ADSRStateType::eAttack); break;
            case ADSRStateType::eDecay      :
            case ADSRStateType::eSustain    : ratio = ratios.at(ADSRStateType::eSustain); break;
            case ADSRStateType::eRelease    :
            case ADSRStateType::eNotPlaying : break;
        }
        return ratio;
    }

    type_d
    ADSRState::
    getTypeTargetSpeed(const adsr::ArraySpeeds& speeds) const
    {
        auto speed = static_cast<type_d>(0.);
        switch (getType())
        {
            case ADSRStateType::eAttack     : speed = speeds.at(ADSRStateType::eAttack); break;
            case ADSRStateType::eDecay      :
            case ADSRStateType::eSustain    : speed = speeds.at(ADSRStateType::eDecay); break;
            case ADSRStateType::eRelease    :
            case ADSRStateType::eNotPlaying : speed = speeds.at(ADSRStateType::eRelease); break;
        }
        return speed;
    }


CANTINA_PAN_NAMESPACE_END
