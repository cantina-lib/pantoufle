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
namespace cant::pan
{
    class MidiControllerChain final : public MidiProcessor
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiControllerChain(size_m numberVoices);

        void process(MidiNoteInternal& in) override;

        void addController(UPtr<MidiController> controller);
        void receiveControl(const MidiControlInternal& control);

        // will notes need updating in processors?
        // updateMidiNoteStream(_memory, tCurrent);

        /*
         * I mean, we could have a mechanic like,
         * a control's value can decrease as time passes.
         * whatever.
         */
        void update(time_m tCurrent) override;
    private:
        /** -- methods -- **/
        void allocateControls(const Stream<byte_m>& controllerIds);

        /** -- fields -- **/
        size_m m_numberVoices;
        UStream<MidiController> m_controllers;

        Map<byte_m, MidiControlInternal> m_controls;

        // constants
        static CANT_CONSTEXPR size_m c_controllerStartingSize = 50;
    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDICONTROLPROCESSOR_HPP
