
#ifndef CANTINA_PAN_MIDINOTEINPUT_INL
#define CANTINA_PAN_MIDINOTEINPUT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    bool
    MidiNoteInput::
    isPlaying() const
    {
         return m_isPressed;
    }

    CANT_INLINE
    bool
    MidiNoteInput::
    justChangedPlaying() const
    {
        return m_changeFlagUpdateModule->justChanged();
    }

    CANT_INLINE
    tone_i8
    MidiNoteInput::
    getToneNative() const
    {
        return m_data.getToneNative();
    }

    CANT_INLINE
    vel_i8
    MidiNoteInput::
    getVelocityNative() const
    {
        return m_data.getVelocityNative();
    }



CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_MIDINOTEINPUT_INL