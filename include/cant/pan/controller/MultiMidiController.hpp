//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MidiController.hpp>

#include <cant/common/macro.hpp>

namespace cant::pan
{

    class MidiNoteInternal;

    /**
     * MidiController should not grant unguarded access
     * to its Processor _memory to child classes.
     * It updates it, but can give a read-only ref.
     **/
     template <size_m numberBindings>
    class MultiMidiController : protected MidiController
    {
    public:
        void update(time_m tCurrent) override = 0;

        CANT_NODISCARD Stream<byte_m> getControllerIds() const override;
    protected:
        CANT_EXPLICIT MultiMidiController(size_m numberVoices, byte_m channel, Array<byte_m, numberBindings> controllerIds);

        CANT_NODISCARD const MidiNoteInternal& getMemory(size_m voice) const;
        CANT_NODISCARD const MidiControlInternal& getControl(size_m iControl) const;
    private:
        /** -- methods -- **/
        // event functions
        void beforeControlProcess(const MidiControlInternal& control) override = 0;
        void beforeNoteProcess(const MidiNoteInternal& note) override = 0;
        // private inheritance
        void IMPL_receiveControl(const MidiControlInternal& incomingControl) final;
        void IMPL_process(MidiNoteInternal& note) const override = 0;

        /** -- fields -- **/
        byte_m m_channel;
        Array<byte_m, numberBindings> m_controllerIds;
        Array<MidiControlInternal, numberBindings> m_controls;
    };


}

#include <cant/common/undef_macro.hpp>

#include "MultiMidiController.inl"

#endif //CANTINA_MIDICONTROLLER_HPP
