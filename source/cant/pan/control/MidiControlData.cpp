//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/control/MidiControlData.hpp>

namespace cant::pan
{
    MidiControlData::
    MidiControlData(const byte_m channel, const byte_m controllerId, const byte_m value)
    : m_channel(channel), m_controllerId(controllerId), m_value(value)
    {

    }



}