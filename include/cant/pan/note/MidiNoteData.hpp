//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MIDINOTEDATA_HPP
#define CANTINA_MIDINOTEDATA_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template <typename Tone_T, typename Vel_T>
    class MidiNoteData : MidiNoteDataCompatible
    {
    public:
        /** -- methods -- **/
        CANT_CONSTEXPR MidiNoteData();
        MidiNoteData(byte_m channel, Tone_T tone, Vel_T velocity);
        template <typename Tone_U, typename Vel_U>
        CANT_EXPLICIT MidiNoteData(const MidiNoteData<Tone_U, Vel_U>& other);
        MidiNoteData(const MidiNoteData &);

        // Shouldn't be used with tone_m/vel_m
        CANT_NODISCARD bool operator==(const MidiNoteData& data) const;
        CANT_NODISCARD bool operator!=(const MidiNoteData& data) const;

        CANT_NODISCARD byte_m getChannel() const override;
        CANT_NODISCARD tone_m getTone() const override;;
        CANT_NODISCARD vel_m getVelocity() const override;

        CANT_NODISCARD bool isPressed() const override;
    protected:
        /** -- fields -- **/
        byte_m m_channel;
        Tone_T m_tone;
        Vel_T m_velocity;
    };


    typedef MidiNoteData<tone_mint, vel_mint> MidiNoteInputData;

    class MidiNoteInternalData : public MidiNoteData<tone_m, vel_m>
    {
    public:
        /** -- methods -- **/
        MidiNoteInternalData();
        CANT_EXPLICIT MidiNoteInternalData(const MidiNoteInputData& input);

        void setTone(tone_m tone);
        void setVelocity(vel_m velocity);
        void setPan(pan_m pan);

        CANT_NODISCARD pan_m getPan() const;
    private:
        /** -- fields -- **/
        pan_m m_pan;
    };

    class MidiNoteOutputData : public MidiNoteData<tone_m, vel_m>
    {
    public:
        /** -- methods -- **/
        MidiNoteOutputData();
        CANT_EXPLICIT MidiNoteOutputData(const MidiNoteInternalData& internal);

        CANT_NODISCARD Array<vel_m, 2> getVelocityPanned() const;

        CANT_NODISCARD pan_m getPan() const;
    private:
        /** -- fields -- **/
        pan_m m_pan;
    };

}

#include <cant/common/undef_macro.hpp>

#include "MidiNoteData.inl"

#endif //CANTINA_MIDINOTEDATA_HPP
