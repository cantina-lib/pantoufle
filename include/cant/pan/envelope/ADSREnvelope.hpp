//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_ADSRENVELOPE_HPP
#define CANTINA_ADSRENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/memory.hpp>
#include <cant/common/formatting.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{

    class ADSRState
    {
    public:
        enum ADSRStateType { eAttack=0, eDecay=2, eSustain=1, eRelease=3, eNotPlaying=4 };
        typedef Array<time_m, 4> ArrayLengths;
        typedef Array<float_m , 2> ArrayVelocityRatios;
        typedef Array<timefunc_m<float_m>, 4> ArrayCallbacks;

    private:
        ADSRStateType _type;
        time_m _tStart;
        bool _flagChangedPlaying;

    private:
        static constexpr const char* m_STATETYPE_CSTRING[] = { "ATTACK", "SUSTAIN", "DECAY", "RELEASE", "NOTPLAYING"};
    private:
        static void REC_compute(ADSRStateType& type, time_m& length, const ArrayLengths& lengths);
        void compute(time_m tCurrent, const ArrayLengths& lengths);

        CANT_NODISCARD static time_m computeTimeStart(time_m tCurrent, time_m length);

        CANT_NODISCARD static bool isSustainFinite(const ArrayLengths& lengths);

        void set(ADSRStateType type, time_m tStart);
        void setFromLength(time_m tCurrent, ADSRStateType type, time_m length);

        CANT_NODISCARD float_m getVelocityRatio(time_m tCurrent, const ADSRState::ArrayCallbacks& callbacks) const;

        void raiseFlagChanged();
        void discardFlagChanged();

        CANT_NODISCARD bool isPlaying() const;
        CANT_NODISCARD bool justChangedPlaying() const;
    public:
        ADSRState();

        CANT_NODISCARD time_m getLength(time_m tCurrent) const;

        void update(time_m tCurrent, const MidiNoteInternal& note, const ArrayLengths& lengths);
        void apply(time_m tCurrent, MidiNoteInternal& note, const ArrayCallbacks& callbacks) const;

        void flushChange();
    };

    class ADSREnvelope final : private VelocityEnvelope
    {
    private:
        /*
         * TODO: right now, if we interrupt the cycle before sustain kicks in,
         * the release doesn't work right. We should then release at the same rate,
         * so it might take longer for the note die.
         */

        static CANT_CONSTEXPR ADSRState::ArrayLengths m_DEFAULT_ADSR_LENGTHS
          = ADSRState::ArrayLengths({30., -1, 50., 80. });
        static CANT_CONSTEXPR ADSRState::ArrayVelocityRatios m_DEFAULT_ADSR_VELOCITIES
          = ADSRState::ArrayVelocityRatios({1., 0.7});
    private:
        /* 0: attack time
         * 2: decay time
         * 1: sustain time, can be infinite -> reserved value (negative)
         * 3: release time
         */
        ADSRState::ArrayLengths _lengths;
        /*
         * 0: attack peak velocity
         * 1: sustain velocity
         */
        ADSRState::ArrayVelocityRatios _velocityRatios;
        ADSRState::ArrayCallbacks _callbacks;

        Stream<ADSRState> _states;
    private:

        void setCallbacks();
        static void checkLengths(const ADSRState::ArrayLengths& lengths);
        static vel_m getBarycentre(time_m lambda,  vel_m v1, vel_m v2);

        ADSREnvelope(size_m numberVoices, const ADSRState::ArrayLengths& lengths, const ADSRState::ArrayVelocityRatios& velocities);
        ADSREnvelope(const ADSREnvelope& adsr) = default;

    public:
        void process(MidiNoteInternal& note) override;

        static UPtr<VelocityEnvelope> make(
                size_m numberVoices,
                const ADSRState::ArrayLengths& lengths = ADSREnvelope::m_DEFAULT_ADSR_LENGTHS,
                const ADSRState::ArrayVelocityRatios& velocities = ADSREnvelope::m_DEFAULT_ADSR_VELOCITIES
        );

        void flushChange() override;
    };
}

#endif //CANTINA_ADSRENVELOPE_HPP
