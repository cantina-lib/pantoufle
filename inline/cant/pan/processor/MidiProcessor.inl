//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDIPROCESSOR_INL
#define CANTINA_TILDE_MIDIPROCESSOR_INL

#pragma once

#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    MidiProcessorMemory::
    MidiProcessorMemory(const size_u numberVoices)
            : m_memory(numberVoices)
    {

    }

    CANT_NODISCARD CANT_INLINE
    size_u
    MidiProcessorMemory::
    getNumberVoices() const
    { return m_memory.getNumberVoices(); }

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_MIDIPROCESSOR_INL
