//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/formatting.hpp>
#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

#include <cant/pan/controller/MidiController.hpp>

#include <cant/common/macro.hpp>

namespace cant::pan
{

    /**
     * MidiController should not grant unguarded access
     * to its Processor _memory to child classes.
     * It updates it, but can give a read-only ref.
     **/
     /*
      *
      *
      */
     template <size_m numberBindings>
    class MultiMidiController : protected MidiController
    {
    private:
        byte_m _channel;
        Array<byte_m, numberBindings> _controllerIds;
        Array<MidiControlInternal, numberBindings> _controls;
    private:
        // event functions
        void beforeControlProcess(const MidiControlInternal& control) override = 0;
        void beforeNoteProcess(const MidiNoteInternal& note) override = 0;
        void IMPL_receiveControl(const MidiControlInternal& incomingControl) final;
        // to be implemented
        void IMPL_process(MidiNoteInternal& note) const override = 0;

    protected:
        CANT_EXPLICIT MultiMidiController(size_m numberVoices, byte_m channel, Array<byte_m, numberBindings> controllerIds);


        CANT_NODISCARD const MidiNoteInternal& getMemory(size_m voice) const;

        CANT_NODISCARD const MidiControlInternal&
        getControl(size_m iControl) const;
    public:
        CANT_NODISCARD Stream<byte_m>
        getControllerIds() const override;

        void update(time_m tCurrent) override = 0;

    };


}

#include <cant/common/undef_macro.hpp>

#include "MultiMidiController.inl"

#endif //CANTINA_MIDICONTROLLER_HPP
