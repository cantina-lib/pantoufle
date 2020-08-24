//
// Created by binabik on 19/07/2020.
//

#ifndef CANTINA_MIDICONTROLDATA_HPP
#define CANTINA_MIDICONTROLDATA_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/types.hpp>
#include <cant/pan/control/MidiControlCompatible.hpp>

#include <cant/common/macro.hpp>
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

        CANT_CONSTEXPR MidiControlData();
        CANT_CONSTEXPR MidiControlData(const MidiControlData&) = default;

        CANT_NODISCARD byte_m getChannel() const override;
        CANT_NODISCARD byte_m getId() const override;
        CANT_NODISCARD byte_m getValue() const override;

    };

    using MidiControlInputData = MidiControlData;
    using MidiControlInput = MidiControlInputData;

    using MidiControlInternal = MidiControlInput;
    /* has had no meaning so far */
    // using MidiControlOutputData = MidiControlData;

}

#include <cant/common/undef_macro.hpp>

#include "MidiControlData.inl"

#endif //CANTINA_MIDICONTROLDATA_HPP
