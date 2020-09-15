//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDICONTROLDATA_INL
#define CANTINA_TILDE_MIDICONTROLDATA_INL

#pragma once

#include <cant/common/macro.hpp>

namespace cant::pan
{
    CANT_INLINE
    id_u8
    MidiControlData::
    getChannel() const
    { return m_channel; }

    CANT_INLINE
    id_u8
    MidiControlData::
    getId() const
    { return m_controllerId; }

    CANT_INLINE
    id_u8
    MidiControlData::
    getValue() const
    { return m_value; }

    CANT_CONSTEXPR
    MidiControlData::
    MidiControlData()
            : m_channel(), m_controllerId(), m_value()
    {}

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDICONTROLDATA_INL
