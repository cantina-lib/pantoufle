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
     template <size_u numberBindings>
    class MultiMidiController : protected MidiController
    {
    public:
        void update(time_d tCurrent) override = 0;

        CANT_NODISCARD Stream<id_u8> getControllerIds() const override;
    protected:
        CANT_EXPLICIT MultiMidiController(size_u numberVoices, id_u8 channel, Array<id_u8, numberBindings> controllerIds);

        CANT_NODISCARD const MidiNoteInternal& getMemory(size_u voice) const;
        CANT_NODISCARD const MidiControlInternal& getControl(size_u iControl) const;
    private:
        /** -- methods -- **/
        // event functions
        void beforeControlProcess(const MidiControlInternal& control) override = 0;
        void beforeNoteProcess(const MidiNoteInternal& note) override = 0;
        // private inheritance
        void IMPL_receiveControl(const MidiControlInternal& incomingControl) final;
        void IMPL_process(MidiNoteInternal& note) const override = 0;

        /** -- fields -- **/
        id_u8 m_channel;
        Array<id_u8, numberBindings> m_controllerIds;
        Array<MidiControlInternal, numberBindings> m_controls;
    };


}

#include <cant/common/undef_macro.hpp>

#include "../../../../inline/cant/pan/controller/MultiMidiController.inl"

#endif //CANTINA_MIDICONTROLLER_HPP
