//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_ADSRENVELOPE_HPP
#define CANTINA_ADSRENVELOPE_HPP

#pragma once

#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{
    enum ADSRState { eAttack=0, eDecay=2, eSustain=1, eRelease=3, eNotPlaying=4 };

    class ADSREnvelope final : private VelocityEnvelope
    {
    private:
        /*
         * TODO: right now, if we interrupt the cycle before sustain kicks in,
         * the release doesn't work right. We should then release at the same rate,
         * so it might take longer for the note die.
         */
        typedef std::array<time_m, 4> ArrayLength;
        typedef std::array<float_m , 2> ArrayVelocityRatios;
        typedef std::array<timefunc_m<float_m>, 4> ArrayCallback;

        static CANT_CONSTEXPR ArrayLength m_DEFAULT_ADSR_LENGTHS = ArrayLength({30., -1, 50., 30. });
        static CANT_CONSTEXPR ArrayVelocityRatios m_DEFAULT_ADSR_VELOCITIES = ArrayVelocityRatios({1., 0.7});
    private:
        /* 0: attack time
         * 2: decay time
         * 1: sustain time, can be infinite -> reserved value (-1, negative?)
         * 3: release time
         */
        ArrayLength _lengths;
        /*
         * 0: attack peak velocity
         * 1: sustain velocity
         */
        ArrayVelocityRatios _velocityRatios;
        ArrayCallback _callbacks;
    private:
        void REC_computeState(ADSRState& state, time_m& length) const;
        void computeState(ADSRState &state, time_m &stateLength, time_m noteLength) const;

        CANT_NODISCARD bool isSustainFinite() const;

        void updateNote(MidiNoteInternal& note, ADSRState state, time_m stateLength) const;

        static bool isPlayingState(ADSRState state);

        CANT_NODISCARD float_m computeVelocityRatio(ADSRState state, time_m stateLength) const;

        void setCallbacks();
        static void checkLengths(const ArrayLength& lengths);
        static vel_m getBarycentre(time_m lambda,  vel_m v1, vel_m v2);
        ADSREnvelope(const ArrayLength& lengths, const ArrayVelocityRatios& velocities);
        ADSREnvelope(const ADSREnvelope& adsr) = default;

    public:
        void apply(time_m tCurrent, MidiNoteInternal& note) const override;

        static UPtr<VelocityEnvelope> make(
                const ADSREnvelope::ArrayLength& lengths = ADSREnvelope::m_DEFAULT_ADSR_LENGTHS,
                const ADSREnvelope::ArrayVelocityRatios& velocities = ADSREnvelope::m_DEFAULT_ADSR_VELOCITIES
        );
    };
}

#endif //CANTINA_ADSRENVELOPE_HPP
