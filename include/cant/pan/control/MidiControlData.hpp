//
// Created by binabik on 19/07/2020.
//

#ifndef CANTINA_MIDICONTROLDATA_HPP
#define CANTINA_MIDICONTROLDATA_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/types.hpp>
#include <cant/pan/control/MidiControlCompatible.hpp>


namespace cant::midi
{
    class MidiControlData : MidiControlCompatible
    {
    private:
        byte_m _controllerId;
        byte_m _value;
    public:
        MidiControlData(const byte_m controllerId, const byte_m value)
        : _controllerId(controllerId), _value(value)
        {

        }

        CANT_CONSTEXPR MidiControlData() : _controllerId(), _value() {}
        CANT_CONSTEXPR MidiControlData(const MidiControlData&) = default;

        CANT_NODISCARD byte_m getControllerId() const override { return _controllerId; }
        CANT_NODISCARD byte_m getValue() const override { return _value; }

        friend std::ostream& operator<<(std::ostream& out, const MidiControlData& data)
        {
            return out << fmt::format("[data] [{0}, {1}]", data.getControllerId(), data.getValue());
        }

    };

    using MidiControlInputData = MidiControlData;
    using MidiControlInput = MidiControlInputData;
    /* has no meaning right now */
    // using MidiControlOutputData = MidiControlData;

}

#endif //CANTINA_MIDICONTROLDATA_HPP
