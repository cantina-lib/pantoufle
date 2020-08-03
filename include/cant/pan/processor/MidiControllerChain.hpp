//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDICONTROLPROCESSOR_HPP
#define CANTINA_MIDICONTROLPROCESSOR_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/controller/MidiController.hpp>

namespace cant::pan
{
    class MidiControllerChain final : public MidiProcessorMemory
    {
    private:
        UMap<byte_m, MidiController> _controllers;
    public:
        void processVoice(size_m iVoice, MidiNoteInternal& in) override;

        CANT_EXPLICIT MidiControllerChain(size_m numberVoices);

        void setController(UPtr<MidiController> controller);
        void processControl(const MidiControlInternal& control);

        // will notes need updating in processors?
        // updateMidiNoteStream(_memory, tCurrent);

        /*
         * I mean, we could have a mechanic like,
         * a control's value can decrease as time passes.
         * whatever.
         */
        void update(time_m tCurrent) override;

    };
}

#endif //CANTINA_MIDICONTROLPROCESSOR_HPP
