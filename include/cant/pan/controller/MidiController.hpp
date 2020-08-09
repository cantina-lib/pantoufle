//
// Created by binabik on 05/08/2020.
//

#ifndef CANTINA_TILDE_MIDICONTROLLER_HPP
#define CANTINA_TILDE_MIDICONTROLLER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

namespace cant::pan
{
    class MidiController : public MidiProcessorMemory
    {
    private:
        // private inheritance
        virtual void IMPL_receiveControl(const MidiControlInternal& control) = 0;
        virtual void IMPL_process(MidiNoteInternal& note) const = 0;

        void updateVoice(const MidiNoteInternal& note);
    protected:
        CANT_EXPLICIT MidiController(size_m numberVoices);
        // event functions
        virtual void beforeControlProcess(const MidiControlInternal& control) = 0;
        /**
         * State changes in the controller as side-effects should be called here.
         * Controller will not be allowed to mutate in IMPL_processVoice,
         * but will be automatically updated in update.
         **/
        virtual void beforeNoteProcess(const MidiNoteInternal& note) = 0;
    public:
        void update(time_m tCurrent) override = 0;

        /*
         * won't have to call it regularily,
         * so it's fine returning a copy
         */
        CANT_NODISCARD virtual Stream<byte_m> getControllerIds() const = 0;

        void receiveControl(const MidiControlInternal& control);
        void process(MidiNoteInternal& internal) final;
    };
}

#endif //CANTINA_TILDE_MIDICONTROLLER_HPP
