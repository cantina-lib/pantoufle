//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDICONTROLPROCESSOR_HPP
#define CANTINA_MIDICONTROLPROCESSOR_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class Clock;

    class MidiControllerChain final : public MidiProcessor
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiControllerChain(size_u numberVoices);

        void process(MidiNoteInternal& in) override;

        void addController(UPtr<MidiController> controller);
        void receiveControl(const MidiControlInternal& control);

    private:
        /** -- methods -- **/
        void allocateControls(const Stream<id_u8>& controllerIds);

        /** -- fields -- **/
        size_u m_numberVoices;
        UStream<MidiController> m_controllers;

        Map<id_u8, MidiControlInternal> m_controls;

        // constants
        static CANT_CONSTEXPR size_u c_controllerStartingSize = 50;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDICONTROLPROCESSOR_HPP
