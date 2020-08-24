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
    CANT_INLINE MidiNoteData<Tone_T, Vel_T>::MidiNoteData(byte_m channel, Tone_T tone, Vel_T velocity)
            : _channel(channel), _tone(tone), _velocity(velocity)
    {

    }

    template<typename Tone_T, typename Vel_T>
    template<typename Tone_U, typename Vel_U>
    CANT_INLINE MidiNoteData<Tone_T, Vel_T>::MidiNoteData(const MidiNoteData <Tone_U, Vel_U> &other)
            : _channel(other.getChannel()),
              _tone(static_cast<Tone_T>(other.getTone())),
              _velocity(static_cast<Vel_T>(other.getVelocity()))
    {

    }

    template<typename Tone_T, typename Vel_T>
    CANT_CONSTEXPR MidiNoteData<Tone_T, Vel_T>::MidiNoteData()
            : _channel(), _tone(), _velocity()
    {

    }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE bool MidiNoteData<Tone_T, Vel_T>::operator==(const MidiNoteData &data) const
    {
        return data._channel == _channel
               && data._tone == _tone
               && data._velocity== _velocity;
    }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE bool MidiNoteData<Tone_T, Vel_T>::operator!=(const MidiNoteData &data) const
    {
        return !operator==(data);
    }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE byte_m MidiNoteData<Tone_T, Vel_T>::getChannel() const
    { return _channel; }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE tone_m MidiNoteData<Tone_T, Vel_T>::getTone() const
    { return static_cast<tone_m>(_tone); }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE vel_m MidiNoteData<Tone_T, Vel_T>::getVelocity() const
    { return static_cast<vel_m>(_velocity); }

    template<typename Tone_T, typename Vel_T>
    CANT_NODISCARD CANT_INLINE bool MidiNoteData<Tone_T, Vel_T>::isPressed() const
    { return static_cast<bool>(_velocity); }


    CANT_INLINE void
    MidiNoteInternalData::
    setTone(const tone_m tone)
    {
        _tone = tone;
    }

    CANT_INLINE void
    MidiNoteInternalData::
    setVelocity(const vel_m velocity)
    {
        _velocity = velocity;
    }

    CANT_INLINE void
    MidiNoteInternalData::
    setPan(const pan_m pan)
    {
        _pan = std::clamp(pan, static_cast<pan_m>(-1), static_cast<pan_m>(1));
    }

    CANT_NODISCARD CANT_INLINE pan_m
    MidiNoteInternalData::
    getPan() const
    {
        return _pan;
    }

    CANT_NODISCARD CANT_INLINE pan_m
    MidiNoteOutputData::
    getPan() const
    {
        return _pan;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTEDATA_INL
