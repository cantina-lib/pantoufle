//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTE_INL
#define CANTINA_TILDE_MIDINOTE_INL

#pragma once

#include <cant/common/macro.hpp>

namespace cant::pan
{
    template<class Data_T>
    MidiNote<Data_T>::MidiNote(size_m voice, byte_m channel, tone_m tone, vel_m velocity)
            : _data(channel, tone, velocity), _voice(voice), _tStart()
    {

    }

    template<class Data_T>
    MidiNote<Data_T>::MidiNote(size_m voice)
            : _data(),  _voice(voice), _tStart()
    {

    }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE const Data_T &MidiNote<Data_T>::getData() const
    { return _data; }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE size_m MidiNote<Data_T>::getVoice() const
    { return _voice; }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE byte_m MidiNote<Data_T>::getChannel() const
    { return _data.getChannel(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE tone_m MidiNote<Data_T>::getTone() const
    { return _data.getTone(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE vel_m MidiNote<Data_T>::getVelocity() const
    { return _data.getVelocity(); }

    template<class Data_T>
    CANT_NODISCARD CANT_INLINE time_m MidiNote<Data_T>::getStartingTime() const
    { return _tStart; }


    CANT_NODISCARD CANT_INLINE bool
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
    time_m
    MidiNoteInternal::
    getLength(const time_m tCurrent) const
    { return tCurrent - _tStart; }

    CANT_INLINE
    void
    MidiNoteInternal::setPlaying(bool isPlaying)
    { _isPlaying = isPlaying; }

    CANT_INLINE void MidiNoteInternal::setChangedPlaying(const bool justChanged)
    { _justChangedPlaying = justChanged; }

    CANT_INLINE void MidiNoteInternal::setChangedTone(const bool justChanged)
    { _justChangedTone = justChanged; }

    CANT_INLINE void MidiNoteInternal::setTone(const tone_m tone)
    { _data.setTone(tone); }

    CANT_INLINE void MidiNoteInternal::setVelocity(const vel_m velocity)
    { _data.setVelocity(velocity); }

    CANT_INLINE void MidiNoteInternal::setPan(const pan_m pan)
    { _data.setPan(pan); }

    CANT_NODISCARD CANT_INLINE pan_m MidiNoteInternal::getPan() const
    { return _data.getPan(); }

    CANT_NODISCARD CANT_INLINE bool MidiNoteInternal::isPlaying() const
    { return _isPlaying; }

    CANT_NODISCARD CANT_INLINE bool MidiNoteInternal::justChangedPlaying() const
    { return _justChangedPlaying; }

    CANT_NODISCARD CANT_INLINE bool MidiNoteInternal::justChangedTone() const
    { return _justChangedTone; }

    CANT_NODISCARD CANT_INLINE vel_m MidiNoteOutput::getVelocity() const
    { return _data.getVelocity(); }


    CANT_NODISCARD CANT_INLINE vel_m
    MidiNoteOutput::
    getVelocityPlaying() const
    {
        return isPlaying() ? getVelocity() : static_cast<vel_m>(0);
    }

    CANT_NODISCARD CANT_INLINE time_m MidiNoteOutput::getLength(const time_m tCurrent) const
    { return tCurrent - _tStart; }

    CANT_NODISCARD CANT_INLINE Array<vel_m, 2> MidiNoteOutput::getVelocityPanned() const
    { return _data.getVelocityPanned(); }

    CANT_NODISCARD CANT_INLINE pan_m MidiNoteOutput::getPan() const
    { return _data.getPan(); }

    CANT_NODISCARD CANT_INLINE bool MidiNoteOutput::isPlaying() const
    { return _isPlaying; }

    CANT_NODISCARD CANT_INLINE bool MidiNoteOutput::justChangedPlaying() const
    { return _justChangedPlaying; }

    CANT_NODISCARD CANT_INLINE bool MidiNoteOutput::justChangedTone() const
    { return _justChangedTone; }

    CANT_NODISCARD CANT_INLINE bool MidiNoteOutput::justStarted() const
    { return _justChangedPlaying && isPlaying(); }

    CANT_NODISCARD CANT_INLINE bool MidiNoteOutput::justStopped() const
    { return _justChangedPlaying && !isPlaying(); }

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTE_INL
