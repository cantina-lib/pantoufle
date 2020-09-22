
#ifndef CANTINA_PAN_ADSRSTATE_HPP
#define CANTINA_PAN_ADSRSTATE_HPP

#pragma once

#include <cant/maths/physics/MagnetisedFunction.hpp>

#include <cant/pan/timer/ChangeFlagUpdatable.hpp>

#include <cant/pan/envelope/adsr_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    class ADSRState : public ChangeFlagUpdatable
    {
    public:
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

        // to allow for smooth changes.
        typedef maths::MagnetisedFunction<type_d, time_d,type_d> VelocityOscillator;

        // to flag changes
        class ChangeFlagUpdateModule : public ChangeFlagUpdatable
        {
        public:
            /** -- friends -- **/
            friend class ADSRState;
        };

        /** -- methods -- **/
        // should obviously only constructed by the envelope it is owned by.
        CANT_EXPLICIT ADSRState();

        void update(const ADSREnvelope *env, time_d tDelta);
        void update(const ADSREnvelope *env, const MidiNoteInternal &note);

        void apply(MidiNoteInternal &note) const;

        CANT_NODISCARD ADSRStateType getType() const;
        CANT_NODISCARD time_d getLength() const;

    private:
        /** -- methods -- **/

        CANT_NODISCARD type_d getVelocityRatio() const;

        void compute(const ADSREnvelope *env, time_d tDelta);
        void computeVelocityRatio(time_d tDelta);

        void setTypeLength(const ADSREnvelope *env, ADSRStateType type, time_d length);
        void setTypeLengthManual(const ADSREnvelope *env, ADSRStateType type);
        void setType(ADSRStateType);

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
         * as such, it is not null of Sustain and NotPlaying,
         * but gives you the speed at which the ratio should stabilise.
         */
        CANT_NODISCARD type_d getTypeTargetSpeed(const adsr::ArraySpeeds& speeds) const;

        /** -- fields -- **/
        ADSRStateType m_type;
        time_d m_length;

        UPtr<VelocityOscillator> m_oscillator;

        UPtr<ChangeFlagUpdateModule> m_changeFlagModule;

        /** -- friends -- **/
        friend class ADSREnvelope;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/envelope/ADSRState.inl>

#endif //CANTINA_PAN_ADSRSTATE_HPP