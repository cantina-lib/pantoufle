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
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiControlData : MidiControlCompatible
    {
    public:
        /** -- methods -- **/
        MidiControlData(id_u8 channel, id_u8 controllerId, id_u8 value);

        CANT_CONSTEXPR MidiControlData();
        CANT_CONSTEXPR MidiControlData(const MidiControlData&) = default;

        CANT_NODISCARD id_u8 getChannel() const override;
        CANT_NODISCARD id_u8 getId() const override;
        CANT_NODISCARD id_u8 getValue() const override;
    private:
        /** -- fields -- **/
        id_u8 m_channel;
        id_u8 m_controllerId;
        id_u8 m_value;

    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/control/MidiControlData.inl>

#endif //CANTINA_MIDICONTROLDATA_HPP
