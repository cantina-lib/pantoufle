//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDICONTROLDATA_INL
#define CANTINA_TILDE_MIDICONTROLDATA_INL

#pragma once

#include <cant/common/macro.hpp>

namespace cant::pan
{
    CANT_INLINE byte_m MidiControlData::getChannel() const
    { return _channel; }

    CANT_INLINE byte_m MidiControlData::getId() const
    { return _controllerId; }

    CANT_INLINE byte_m MidiControlData::getValue() const
    { return _value; }

    CANT_CONSTEXPR MidiControlData::MidiControlData()
            : _channel(), _controllerId(), _value()
    {

    }

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDICONTROLDATA_INL
