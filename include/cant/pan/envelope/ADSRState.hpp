
#ifndef CANTINA_PAN_ADSRSTATE_HPP
#define CANTINA_PAN_ADSRSTATE_HPP

#pragma once


#include <cant/pan/timer/ChangeFlagUpdatable.hpp>

#include <cant/physics/PhysicsSimulation.hpp>

#include <cant/physics/RigidObject.hpp>
#include <cant/physics/CollisionObject.hpp>

#include <cant/pan/envelope/adsr_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    class ADSRState : public ChangeFlagUpdatable
    {
    public:
        /** -- typedefs -- **/
        typedef physics::PhysicsSimulation<type_d, type_d, time_d, 1> Simulation;
        typedef physics::KineticState<type_d, type_d, time_d, 1> VelocityState;
        typedef physics::RigidObject<type_d, type_d, time_d, 1> VelocityObject;
        typedef physics::PhysicalState<type_d, 1> TargetState;
        typedef physics::CollisionObject<type_d, type_d, 1> TargetObject;
        typedef physics::PhysicalShape<type_d, 1> Shape;


        /** -- internal structures -- **/
        enum ADSRStateType
        {
            eAttack     = 0, // he attac
            eDecay      = 2, // he decay
            // but most importantly
            eSustain    = 1, // he won't throw sustain away
            eRelease    = 3,
            eNotPlaying = 4
        };

        // to flag changes
        class ChangeFlagUpdateModule : public ChangeFlagUpdatable
        {
        public:
            /** -- friends -- **/
            friend class ADSRState;
        };

        /** -- methods -- **/
        // should obviously only constructed by the envelope it is owned by.
        ADSRState();

        void updateTypeLength(const ADSREnvelope *env, time_d tDelta);
        void updateTypeLengthManual(const ADSREnvelope *env, const MidiNoteInternal &note);

        void apply(MidiNoteInternal &note) const;

        CANT_NODISCARD ADSRStateType getType() const;
        CANT_NODISCARD time_d getLength() const;

    private:
        /** -- methods -- **/

        CANT_NODISCARD type_d getVelocityRatio() const;

        void setTypeLength(const ADSREnvelope* env, ADSRStateType type, time_d length);
        void setTypeLengthManual(const ADSREnvelope *env, ADSRStateType type);
        void setType(const ADSREnvelope* env, ADSRStateType);

        void updateSimulation(time_d tDelta);
        void resetTarget(const ADSREnvelope* env);

        CANT_NODISCARD bool justChangedPlaying() const;
        void raiseFlagChangedPlaying() const;

        CANT_NODISCARD bool isPlaying() const;
        CANT_NODISCARD bool isVarying() const;


        // static methods
        static void computeTypeLengthRecursive(ADSRStateType& type, time_d& length, const adsr::ArrayLengths& lengths);

        // returns actual velocity ratio for current type (will be null if not playing)
        CANT_NODISCARD type_d getTypeTargetVelocityRatio(const adsr::ArrayVelocityRatios& ratios) const;
        /*
         * returns speed at which the velocity ratio should change to get to target.
         */
        CANT_NODISCARD type_d getTypeTargetSpeed(const adsr::ArraySpeeds& speeds) const;

        /** -- fields -- **/
        ADSRStateType m_type;
        time_d m_length;
        type_d m_currentTargetVelocity;

        UPtr<Simulation> m_physicsSimulation;

        ShPtr<VelocityObject> m_object;
        ShPtr<TargetObject> m_target;


        UPtr<ChangeFlagUpdateModule> m_changeFlagModule;

        /** -- constants -- **/
        static CANT_CONSTEXPR type_d c_strength = 10;
        static CANT_CONSTEXPR type_d c_resistance = 0.2;
        static CANT_CONSTEXPR type_d c_weight = 10000;
        static CANT_CONSTEXPR type_d c_radius = 0.05;

        /** -- friends -- **/
        friend class ADSREnvelope;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/envelope/ADSRState.inl>

#endif //CANTINA_PAN_ADSRSTATE_HPP