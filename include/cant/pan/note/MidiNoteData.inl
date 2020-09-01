//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTEDATA_INL
#define CANTINA_TILDE_MIDINOTEDATA_INL

#pragma once

#include <cant/common/macro.hpp>

namespace cant::pan
{
    template<typename Tone_T, typename Vel_T>
    CANT_INLINE
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData(byte_m channel, Tone_T tone, Vel_T velocity)
            : m_channel(channel), m_tone(tone), m_velocity(velocity)
    {

    }

    template<typename Tone_T, typename Vel_T>
    template<typename Tone_U, typename Vel_U>
    CANT_INLINE
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData(const MidiNoteData <Tone_U, Vel_U> &other)
            : m_channel(other.getChannel()),
              m_tone(static_cast<Tone_T>(other.getTone())),
              m_velocity(static_cast<Vel_T>(other.getVelocity()))
    {

    }

    template<typename Tone_T, typename Vel_T>
    CANT_CONSTEXPR
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData()
            : m_channel(), m_tone(), m_velocity()
    {

    }

    template<typename Tone_T, typename Vel_T>
    MidiNoteData<Tone_T, Vel_T>::
    MidiNoteData(const MidiNoteData &) = default;

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
    byte_m
    MidiNoteData<Tone_T, Vel_T>::
    getChannel() const
    { return m_channel; }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    tone_m
    MidiNoteData<Tone_T, Vel_T>::
    getTone() const
    { return static_cast<tone_m>(m_tone); }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    vel_m
    MidiNoteData<Tone_T, Vel_T>::
    getVelocity() const
    { return static_cast<vel_m>(m_velocity); }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteData<Tone_T, Vel_T>::
    isPressed() const
    { return static_cast<bool>(m_velocity); }

    CANT_INLINE
    void
    MidiNoteInternalData::
    setTone(const tone_m tone)
    {
        m_tone = tone;
    }

    CANT_INLINE
    void
    MidiNoteInternalData::
    setVelocity(const vel_m velocity)
    {
        m_velocity = velocity;
    }

    CANT_INLINE
    void
    MidiNoteInternalData::
    setPan(const pan_m pan)
    {
        m_pan = std::clamp(pan, static_cast<pan_m>(-1), static_cast<pan_m>(1));
    }

    CANT_NODISCARD CANT_INLINE
    pan_m
    MidiNoteInternalData::
    getPan() const
    {
        return m_pan;
    }

    CANT_NODISCARD CANT_INLINE
    pan_m
    MidiNoteOutputData::
    getPan() const
    {
        return m_pan;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTEDATA_INL
