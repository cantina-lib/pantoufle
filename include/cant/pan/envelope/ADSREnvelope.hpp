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
CANTINA_PAN_NAMESPACE_BEGIN

    class ADSRState
    {
    public:
        /** -- internal structures -- **/
        enum ADSRStateType
        {
            eAttack=0,
            eDecay=2,
            eSustain=1,
            eRelease=3,
            eNotPlaying=4
        };
        typedef Array<time_d, 4> ArrayLengths;
        typedef Array<type_d , 2> ArrayVelocityRatios;
        typedef Array<timecallback_f<type_d>, 4> ArrayCallbacks;

        /** -- methods -- **/
        ADSRState();

        void update(time_d tCurrent, const MidiNoteInternal& note, const ArrayLengths& lengths);
        void apply(time_d tCurrent, MidiNoteInternal& note, const ArrayCallbacks& callbacks) const;
        void flushChange();

        CANT_NODISCARD time_d getLength(time_d tCurrent) const;
        CANT_NODISCARD ADSRStateType getType() const;
    private:
        /** -- methods -- **/

        CANT_NODISCARD type_d getVelocityRatio(time_d tCurrent, const ADSRState::ArrayCallbacks& callbacks) const;

        void compute(time_d tCurrent, const ArrayLengths& lengths);

        void set(ADSRStateType type, time_d tStart);
        void setFromLength(time_d tCurrent, ADSRStateType type, time_d length);

        void raiseFlagChanged();
        void discardFlagChanged();

        CANT_NODISCARD bool isPlaying() const;
        CANT_NODISCARD bool justChangedPlaying() const;

        // static methods
        CANT_NODISCARD static time_d computeTimeStart(time_d tCurrent, time_d length);
        CANT_NODISCARD static bool isSustainFinite(const ArrayLengths& lengths);
        static void REC_compute(ADSRStateType& type, time_d& length, const ArrayLengths& lengths);

        /** -- fields -- **/
        ADSRStateType m_type;
        time_d m_tStart;
        bool m_flagChangePlaying;
    };

    class ADSREnvelope final : private VelocityEnvelope
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<VelocityEnvelope> make(
                size_u numberVoices,
                const ADSRState::ArrayLengths& lengths = ADSREnvelope::c_defaultADSRLengths,
                const ADSRState::ArrayVelocityRatios& velocities = ADSREnvelope::c_defaultADSRVelocities
        );

        void process(MidiNoteInternal& note) override;

        void flushChange() override;
    private:
        /** -- methods -- **/
        ADSREnvelope(size_u numberVoices, const ADSRState::ArrayLengths& lengths, const ADSRState::ArrayVelocityRatios& velocities);
        ADSREnvelope(const ADSREnvelope& adsr) = default;

        void setCallbacks();

        // static methods
        static void checkLengths(const ADSRState::ArrayLengths& lengths);

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
        c_defaultADSRLengths = {20., -1, 50., 20. };


        CANT_CONSTEXPR
        static
        ADSRState::ArrayVelocityRatios
        c_defaultADSRVelocities = {1., 0.7 };

    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_ADSRENVELOPE_HPP
