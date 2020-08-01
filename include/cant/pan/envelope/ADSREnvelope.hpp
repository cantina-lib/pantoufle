//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_ADSRENVELOPE_HPP
#define CANTINA_ADSRENVELOPE_HPP

#pragma once

#include <string>
#include <iostream>

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/note/EnvelopedMidiNote.hpp>

namespace cant::pan
{
    enum ADSRStateType { eAttack=0, eDecay=2, eSustain=1, eRelease=3, eNotPlaying=4 };

    CANT_CONSTEXPR static const char* ADSR_STATYPE_NAMES[] = { "ATTACK", "SUSTAIN", "DECAY", "RELEASE", "NOT_PLAYING" };

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
        ArrayVelocityRatios _velocities;
        ArrayCallback _callbacks;
        ADSRStateType _type;
        time_m _tTypeStart;
    private: // private inheritance, called in MidiEnvelope
        void IMPL_Velocity_reset() override;
        void IMPL_Velocity_update(const EnvelopedMidiNote* envNote) override;
        CANT_NODISCARD std::string print() const override;
    private:
        void REC_updateType(ADSRStateType& type, time_m& typeLength) const;
        void updateType(const EnvelopedMidiNote* envNote);

        void setType(ADSRStateType);
        void setType(ADSRStateType, time_m typeLength);

        CANT_NODISCARD time_m getTypeLength() const;

        void setCallbacks();
        static vel_m getBarycentre(time_m lambda,  vel_m v1, vel_m v2);

        static void checkLengths(const ArrayLength& lengths);
        CANT_NODISCARD bool isSustainFinite() const;

        ADSREnvelope(const ArrayLength& lengths, const ArrayVelocityRatios& velocities);
        ADSREnvelope(const ADSREnvelope& adsr) = default;

    protected:
        CANT_NODISCARD UPtr<VelocityEnvelope> IMPL_clone() const override;

        CANT_NODISCARD float_m getVelocityRatio() const override;
        CANT_NODISCARD bool isEnvelopePlaying() const override;
    public:
        static UPtr<VelocityEnvelope> make(
                const ADSREnvelope::ArrayLength& lengths = ADSREnvelope::m_DEFAULT_ADSR_LENGTHS,
                const ADSREnvelope::ArrayVelocityRatios& velocities = ADSREnvelope::m_DEFAULT_ADSR_VELOCITIES
        );

        friend std::ostream& operator<<(std::ostream& out, const ADSREnvelope* env);
    };

    std::ostream& operator<<(std::ostream& out, const ADSREnvelope* env);
}

#endif //CANTINA_ADSRENVELOPE_HPP
