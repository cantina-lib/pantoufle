//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDIENVELOPE_INL
#define CANTINA_TILDE_MIDIENVELOPE_INL

#pragma once

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template<typename T>
    CANT_NODISCARD CANT_INLINE time_m
    MidiEnvelope<T>::
    getCurrentTime() const
    {
        return _tCurrent;
    }

    template<typename T>
    CANT_INLINE
    MidiEnvelope<T>::
    MidiEnvelope(size_m numberVoices)
            : MidiProcessorMemory(numberVoices),
              _tCurrent()
    {

    }

    template<typename T>
    CANT_INLINE void
    MidiEnvelope<T>::
    update(const time_m tCurrent)
    {
        _tCurrent = tCurrent;
    }

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDIENVELOPE_INL
