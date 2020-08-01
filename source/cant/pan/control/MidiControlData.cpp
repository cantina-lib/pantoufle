//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/control/MidiControlData.hpp>

namespace cant::pan
{
    MidiControlData::
    MidiControlData(const byte_m channel, const byte_m controllerId, const byte_m value)
    : _channel(channel), _controllerId(controllerId), _value(value)
    {

    }
}