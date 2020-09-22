//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_PAN_ADSRENVELOPE_HPP
#define CANTINA_PAN_ADSRENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/envelope/adsr_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class ADSRState;

    class ADSREnvelope : private VelocityEnvelope
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<VelocityEnvelope> make
                (
                        size_u numberVoices,
                        const adsr::ArrayLengths& lengths           = ADSREnvelope::c_defaultADSRLengths,
                        const adsr::ArrayVelocityRatios& velocities = ADSREnvelope::c_defaultADSRVelocities
                );
        void process(MidiNoteInternal& note) override;

        // implementation of Listener interface
        // mentioned in MidiEnvelopeModule
        void subscribe(event::Ptr<MidiTimer> timer) final;
        void unsubscribe(event::Ptr<MidiTimer> timer) final;

    private:
        /** -- methods -- **/
        ADSREnvelope
                (
                        size_u numberVoices,
                        const adsr::ArrayLengths& lengths,
                        const adsr::ArrayVelocityRatios& velocities
                );

        CANT_NODISCARD static adsr::ArraySpeeds computeSpeeds(const adsr::ArrayLengths& lengths, const adsr::ArrayVelocityRatios& ratios);

        // private inheritance
        void updateDelta(time_d tDelta) override;

        // static methods
        static void checkLengths(const adsr::ArrayLengths& lengths);
        CANT_NODISCARD static bool isSustainFinite(const adsr::ArrayLengths& lengths);


        /** -- fields -- **/
        /*
         * 0: attack time
         * 1: sustain time, can be infinite -> reserved value (negative)
         * 2: decay time
         * 3: release time
         */
        adsr::ArrayLengths m_lengths;
        /*
         * 0: attack peak velocity
         * 1: sustain velocity
         */
        adsr::ArrayVelocityRatios m_velocityRatios;

        /*
         * inferred from the other two
         * The lengths won't actually be respected, they are only targets,
         * and the velocity ratios will change at the rates in m_speeds.
         * positive!!!!
         */
        adsr::ArraySpeeds m_speeds;

        Stream<ADSRState> m_states;

        // constants
        CANT_CONSTEXPR static adsr::ArrayLengths c_defaultADSRLengths = {
                // { ADSRState::ADSRStateType::eAttack,  100. },
                // { ADSRState::ADSRStateType::eDecay,   50. },
                // { ADSRState::ADSRStateType::eRelease, 100. }
                30.,
                -1.,
                50.,
                30.
        };

        CANT_CONSTEXPR static adsr::ArrayVelocityRatios c_defaultADSRVelocities = {
                // { ADSRState::ADSRStateType::eAttack, 1. },
                // { ADSRState::ADSRStateType::eSustain, 0.7 }
                1.,
                0.7
        };

        /** -- friends - **/
        friend class ADSRState;
    };


CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_ADSRENVELOPE_HPP
