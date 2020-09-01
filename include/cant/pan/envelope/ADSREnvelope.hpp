//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_ADSRENVELOPE_HPP
#define CANTINA_ADSRENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/memory.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    class ADSRState
    {
    public:
        /** -- internal structures -- **/
        enum ADSRStateType { eAttack=0, eDecay=2, eSustain=1, eRelease=3, eNotPlaying=4 };
        typedef Array<time_m, 4> ArrayLengths;
        typedef Array<float_m , 2> ArrayVelocityRatios;
        typedef Array<timefunc_m<float_m>, 4> ArrayCallbacks;

        /** -- methods -- **/
        ADSRState();

        void update(time_m tCurrent, const MidiNoteInternal& note, const ArrayLengths& lengths);
        void apply(time_m tCurrent, MidiNoteInternal& note, const ArrayCallbacks& callbacks) const;
        void flushChange();

        CANT_NODISCARD time_m getLength(time_m tCurrent) const;
    private:
        /** -- methods -- **/

        CANT_NODISCARD float_m getVelocityRatio(time_m tCurrent, const ADSRState::ArrayCallbacks& callbacks) const;

        void compute(time_m tCurrent, const ArrayLengths& lengths);

        void set(ADSRStateType type, time_m tStart);
        void setFromLength(time_m tCurrent, ADSRStateType type, time_m length);


        void raiseFlagChanged();
        void discardFlagChanged();

        CANT_NODISCARD bool isPlaying() const;
        CANT_NODISCARD bool justChangedPlaying() const;

        // static methods
        CANT_NODISCARD static time_m computeTimeStart(time_m tCurrent, time_m length);
        CANT_NODISCARD static bool isSustainFinite(const ArrayLengths& lengths);
        static void REC_compute(ADSRStateType& type, time_m& length, const ArrayLengths& lengths);

        /** -- fields -- **/
        ADSRStateType m_type;
        time_m m_tStart;
        bool m_flagChangePlaying;
    };

    class ADSREnvelope final : private VelocityEnvelope
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<VelocityEnvelope> make(
                size_m numberVoices,
                const ADSRState::ArrayLengths& lengths = ADSREnvelope::c_defaultADSRLengths,
                const ADSRState::ArrayVelocityRatios& velocities = ADSREnvelope::c_defaultADSRVelocities
        );

        void process(MidiNoteInternal& note) override;

        void flushChange() override;
    private:
        /** -- methods -- **/
        ADSREnvelope(size_m numberVoices, const ADSRState::ArrayLengths& lengths, const ADSRState::ArrayVelocityRatios& velocities);
        ADSREnvelope(const ADSREnvelope& adsr) = default;

        void setCallbacks();
        static void checkLengths(const ADSRState::ArrayLengths& lengths);
        static vel_m getBarycentre(time_m lambda,  vel_m v1, vel_m v2);

        /** -- fields -- **/
        /* 0: attack time
         * 2: decay time
         * 1: sustain time, can be infinite -> reserved value (negative)
         * 3: release time
         */
        ADSRState::ArrayLengths m_lengths;
        /*
         * 0: attack peak velocity
         * 1: sustain velocity
         */
        ADSRState::ArrayVelocityRatios m_velocityRatios;
        ADSRState::ArrayCallbacks m_callbacks;

        Stream<ADSRState> m_states;

        // constants
        CANT_CONSTEXPR
        static
        ADSRState::ArrayLengths
        c_defaultADSRLengths = {30., -1, 50., 80. };


        CANT_CONSTEXPR
        static
        ADSRState::ArrayVelocityRatios
        c_defaultADSRVelocities = {1., 0.7 };

    };
}
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_ADSRENVELOPE_HPP
