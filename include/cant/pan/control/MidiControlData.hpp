//
// Created by binabik on 19/07/2020.
//

#ifndef CANTINA_MIDICONTROLDATA_HPP
#define CANTINA_MIDICONTROLDATA_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/types.hpp>
#include <cant/pan/control/MidiControlCompatible.hpp>


namespace cant::pan
{
    class MidiControlData : MidiControlCompatible
    {
    private:
        byte_m _channel;
        byte_m _controllerId;
        byte_m _value;
    public:
        MidiControlData(byte_m channel, byte_m controllerId, byte_m value);

        CANT_CONSTEXPR MidiControlData()
        : _channel(), _controllerId(), _value()
        {

        }
        CANT_CONSTEXPR MidiControlData(const MidiControlData&) = default;

        CANT_NODISCARD byte_m getChannel() const override { return _channel; }
        CANT_NODISCARD byte_m getControllerId() const override { return _controllerId; }
        CANT_NODISCARD byte_m getValue() const override { return _value; }

        friend std::ostream& operator<<(std::ostream& out, const MidiControlData& data)
        {
            return out << fmt::format("[data] [{0}, {1}]", data.getControllerId(), data.getValue());
        }

    };

    using MidiControlInputData = MidiControlData;
    using MidiControlInput = MidiControlInputData;

    using MidiControlInternal = MidiControlInput;
    /* has had no meaning so far */
    // using MidiControlOutputData = MidiControlData;

}

#endif //CANTINA_MIDICONTROLDATA_HPP
