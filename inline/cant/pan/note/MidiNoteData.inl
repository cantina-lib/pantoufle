//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTEDATA_INL
#define CANTINA_TILDE_MIDINOTEDATA_INL

#pragma once

#include <cant/maths/maths.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template<typename Tone_T, typename Vel_T>
    CANT_INLINE
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData(id_u8 channel, Tone_T tone, Vel_T velocity)
            : m_channel(channel),
            m_tone(tone),
            m_velocity(velocity)
    {

    }

    template <typename Tone_T, typename Vel_T>
    template <typename Tone_U, typename Vel_U>
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData(const MidiNoteData<Tone_U, Vel_U> &other)
            : m_channel(other.getChannel()),
              m_tone(static_cast<Tone_T>(other.getTone())),
              m_velocity(static_cast<Vel_T>(other.getVelocity()))
    {}

    template <typename Tone_T, typename Vel_T>
    CANT_INLINE
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData()
        : m_channel(),
        m_tone(),
        m_velocity()
    {}


    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteData<Tone_T, Vel_T>::
    operator==(const MidiNoteData &data) const
    {
        return data.m_channel == m_channel
               && data.m_tone == m_tone
               && data.m_velocity == m_velocity;
    }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteData<Tone_T, Vel_T>::
    operator!=(const MidiNoteData &data) const
    {
        return !operator==(data);
    }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    id_u8
    MidiNoteData<Tone_T, Vel_T>::
    getChannel() const
    { return m_channel; }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    tone_d
    MidiNoteData<Tone_T, Vel_T>::
    getTone() const
    { return static_cast<tone_d>(m_tone); }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    vel_d
    MidiNoteData<Tone_T, Vel_T>::
    getVelocity() const
    { return static_cast<vel_d>(m_velocity); }

    CANT_NODISCARD CANT_INLINE
    tone_i8
    MidiNoteInputData::
    getToneNative() const
    {
        return m_tone;
    }

    CANT_NODISCARD CANT_INLINE
    vel_i8
    MidiNoteInputData::
    getVelocityNative() const
    {
        return m_velocity;
    }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInputData::
    isPressed() const
    { return static_cast<bool>(m_velocity); }


    CANT_INLINE
    void
    MidiNoteInternalData::
    setTone(const tone_d tone)
    {
        m_tone = tone;
    }

    CANT_INLINE
    void
    MidiNoteInternalData::
    setVelocity(const vel_d velocity)
    {
        m_velocity = velocity;
    }

    CANT_INLINE
    void
    MidiNoteInternalData::
    setPan(const pan_d pan)
    {
        m_pan = std::clamp(pan, static_cast<pan_d>(-1), static_cast<pan_d>(1));
    }

    CANT_NODISCARD CANT_INLINE
    pan_d
    MidiNoteInternalData::
    getPan() const
    {
        return m_pan;
    }

    CANT_NODISCARD CANT_INLINE
    pan_d
    MidiNoteOutputData::
    getPan() const
    {
        return m_pan;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTEDATA_INL
