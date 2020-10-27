//
// Created by binabik on 22/09/2020.
//

#include <cant/pan/envelope/ADSRState.hpp>
#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/physics/CustomForceField.hpp>
#include <cant/physics/IsotropicPullField.hpp>


#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    ADSRState::
    ADSRState()
            : m_type(ADSRStateType::eNotPlaying),
              m_length(),
              m_currentTargetVelocity(),
              m_flagJustChangedPlaying(false),
              m_tickListener(),
              m_physicsSimulation(std::make_unique<Simulation>()),
              m_object
              (
                      std::make_unique<VelocityObject>
                      (
                          std::make_unique<VelocityState>(c_weight),
                          std::make_unique<Shape>(0., c_radius)
                      )
              ),
              m_target
              (
                      std::make_unique<TargetObject>
                      (
                              std::make_unique<TargetState>(),
                              std::make_unique<Shape>(0., c_radius)
                      )
              )
    {

        m_physicsSimulation->addRigidObject(m_object, static_cast<type_i>(0));
        m_physicsSimulation->addStaticObject(m_target, static_cast<type_i>(0));

        // gravity.
        m_physicsSimulation->addForceField
        (
               static_cast<UPtr<physics::PhysicalForceField<type_d, type_d, time_d, 1>>>
               (
                       std::make_unique<physics::IsotropicPullField<type_d, type_d, time_d, 1>>
                               (
                                       [](type_d dist)
                                       {
                                           return c_strength / (dist * dist);
                                       },
                                       m_target
                               )
               )
        );

        // resistance.
        /*
        m_physicsSimulation->addForceField
        (
               static_cast<UPtr<physics::PhysicalForceField<type_d, type_d, time_d, 1>>>
               (
                       std::make_unique<physics::CustomForceField<type_d, type_d, time_d, 1>>
                               (
                                       [](const auto& state, CANT_MAYBEUNUSED time_d tDelta)
                                       {
                                           return - state->getVelocity()
                                           // * (c_resistance / (tDelta * state->getInverseMass()));
                                           * c_resistance;
                                       }
                               )
               )
        );
         */
    }


    void
    ADSRState::onTimerTick(void *)
    {
        m_flagJustChangedPlaying = false;
    }

    void
    ADSRState::
    updateTypeLengthManual(const ADSREnvelope *env, const MidiNoteInternal &note)
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
    setTypeLengthManual(const ADSREnvelope *env, ADSRStateType type)
    {
        setTypeLength(env, type, static_cast<time_d>(0.));
    }

    void
    ADSRState::
    updateTypeLength(const ADSREnvelope *env, time_d tDelta)
    {
        // starting values.
        ADSRStateType type = m_type;
        time_d length = getLength() + tDelta;

        // recursively computing updated type and length.
        computeTypeLengthRecursive(type, length, env->m_lengths);
        setTypeLength(env, type, length);

        updateSimulation(tDelta);
    }

    void
    ADSRState::
    updateSimulation(time_d tDelta)
    {
        m_physicsSimulation->stepDelta(tDelta);
        type_d ratio = getVelocityRatio();
        if (ratio > static_cast<type_d>(1.) || ratio < static_cast<type_d>(0.))
        {
            ratio = std::clamp<type_d>(ratio, static_cast<type_d>(0), static_cast<type_d>(1));
            m_object->setPosition(ratio);
        }
    }

    void
    ADSRState::
    setTypeLength(const ADSREnvelope* env, ADSRStateType type, time_d length)
    {
        m_length = length;
        setType(env, type);
    }

    void
    ADSRState::
    resetTarget(const ADSREnvelope *env)
    {
        type_d targetRatio = getTypeTargetVelocityRatio(env->m_ratios);
        // set position of target so that the collider can 'support' the physical object.
        targetRatio += targetRatio > getVelocityRatio() ? c_radius : - c_radius;
        m_target->setPosition(targetRatio);
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
            case ADSRStateType::eAttack     : speed = speeds.at(ADSRStateType::eAttack);  break;
            case ADSRStateType::eDecay      : speed = speeds.at(ADSRStateType::eDecay);   break;
            case ADSRStateType::eRelease    : speed = speeds.at(ADSRStateType::eRelease); break;
            case ADSRStateType::eSustain    :
            case ADSRStateType::eNotPlaying : speed = static_cast<type_d>(0);
        }
        return speed;
    }


CANTINA_PAN_NAMESPACE_END
