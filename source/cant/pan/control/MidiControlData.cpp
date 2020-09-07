//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/control/MidiControlData.hpp>

namespace cant::pan
{
    MidiControlData::
    MidiControlData(const id_u8 channel, const id_u8 controllerId, const id_u8 value)
    : m_channel(channel), m_controllerId(controllerId), m_value(value)
    {

    }



}