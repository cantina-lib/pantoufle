//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTE_INL
#define CANTINA_TILDE_MIDINOTE_INL

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template<class Data_T>
    MidiNote<Data_T>::
    MidiNote(size_u voice, id_u8 channel, tone_d tone, vel_d velocity)
            : m_data(channel, tone, velocity), m_voice(voice), m_tStart()
    {

    }

    template<class Data_T>
    MidiNote<Data_T>::
    MidiNote(size_u voice)
            : m_data(), m_voice(voice), m_tStart()
    {

    }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    const Data_T&
    MidiNote<Data_T>::
    getData() const
    { return m_data; }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    size_u
    MidiNote<Data_T>::
    getVoice() const
    { return m_voice; }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    id_u8
    MidiNote<Data_T>::
    getChannel() const
    { return m_data.getChannel(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    tone_d
    MidiNote<Data_T>::
    getTone() const
    { return m_data.getTone(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    vel_d
    MidiNote<Data_T>::
    getVelocity() const
    { return m_data.getVelocity(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE
    time_d
    MidiNote<Data_T>::
    getStartingTime() const
    { return m_tStart; }


    CANT_NODISCARD CANT_INLINE
    MidiNoteInput&
    MidiNoteInput::operator=(const MidiNoteInput&) = default;

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInput::
    isPressed() const
    { return _isPressed; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInput::
    justChangedPlaying() const
    { return _flagChangedPlaying; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInput::
    justChangedTone() const
    { return _flagChangedTone; }


    CANT_NODISCARD CANT_INLINE
    time_d
    MidiNoteInternal::
    getLength(const time_d tCurrent) const
    { return tCurrent - m_tStart; }

    CANT_INLINE
    void
    MidiNoteInternal::setPlaying(bool isPlaying)
    { m_isPlaying = isPlaying; }

    CANT_INLINE
    void
    MidiNoteInternal::
    setChangedPlaying(const bool justChanged)
    { m_justChangedPlaying = justChanged; }

    CANT_INLINE
    void
    MidiNoteInternal::
    setChangedTone(const bool justChanged)
    { m_justChangedTone = justChanged; }

    CANT_INLINE
    void
    MidiNoteInternal::
    setTone(const tone_d tone)
    { m_data.setTone(tone); }

    CANT_INLINE
    void
    MidiNoteInternal::
    setVelocity(const vel_d velocity)
    { m_data.setVelocity(velocity); }

    CANT_INLINE
    void
    MidiNoteInternal::
    setPan(const pan_d pan)
    { m_data.setPan(pan); }

    CANT_NODISCARD CANT_INLINE
    pan_d
    MidiNoteInternal::
    getPan() const
    { return m_data.getPan(); }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInternal::isPlaying() const
    { return m_isPlaying; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInternal::
    justChangedPlaying() const
    { return m_justChangedPlaying; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteInternal::
    justChangedTone() const
    { return m_justChangedTone; }

    CANT_NODISCARD CANT_INLINE
    vel_d
    MidiNoteOutput::
    getVelocity() const
    { return m_data.getVelocity(); }


    CANT_NODISCARD CANT_INLINE
    vel_d
    MidiNoteOutput::
    getVelocityPlaying() const
    {
        return isPlaying() ? getVelocity() : static_cast<vel_d>(0);
    }

    CANT_NODISCARD CANT_INLINE
    time_d
    MidiNoteOutput::
    getLength(const time_d tCurrent) const
    { return tCurrent - m_tStart; }

    CANT_NODISCARD CANT_INLINE
    Array<vel_d, 2>
    MidiNoteOutput::
    getVelocityPanned() const
    { return m_data.getVelocityPanned(); }

    CANT_NODISCARD CANT_INLINE
    pan_d
    MidiNoteOutput::
    getPan() const
    { return m_data.getPan(); }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteOutput::
    isPlaying() const
    { return m_isPlaying; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteOutput::
    justChangedPlaying() const
    { return m_justChangedPlaying; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteOutput::
    justChangedTone() const
    { return m_justChangedTone; }

    CANT_NODISCARD CANT_INLINE
    bool
    MidiNoteOutput::
    justStarted() const
    { return m_justChangedPlaying && isPlaying(); }

    CANT_NODISCARD CANT_INLINE
    bool MidiNoteOutput::
    justStopped() const
    { return m_justChangedPlaying && !isPlaying(); }

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTE_INL
