//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>


namespace cant::pan
{

    /**
     * MidiController should not grant unguarded access
     * to its Processor _memory to child classes.
     * It updates it, but can give a read-only ref
     **/
    class MidiController : protected MidiProcessorMemory
    {
    private:
        byte_m _channel;
        const byte_m _controllerId;
        MidiControlInternal _control;
    private:
        // event functions
        virtual void beforeControlProcess(const MidiControlInternal& incoming) = 0;
        /**
         * State changes in the controller as side-effects should be called here.
         * Controller will not be allowed to mutate in IMPL_processVoice,
         * but will be automatically updated in update.
         **/
        virtual void beforeNoteProcess(size_m iVoice, const MidiNoteInternal& incoming) = 0;
        // to be implemented
        virtual void IMPL_processVoice(size_m iVoice, MidiNoteInternal& incoming) const = 0;
    private:
        CANT_NODISCARD static bool isControllerSet(const MidiController* controller);

        void updateVoice(size_m iVoice, const MidiNoteInternal& note);
    protected:
        CANT_EXPLICIT MidiController(size_m numberVoices, byte_m channel, byte_m controllerId);

        CANT_NODISCARD const MidiNoteInternal& getMemory(size_m iVoice) const { return _memory.at(iVoice); }
    public:
        void processVoice(size_m iVoice, MidiNoteInternal& internal) final;

        CANT_NODISCARD static bool isControllerSet(const UPtr<MidiController>& controller);
        CANT_NODISCARD byte_m getControllerId() const { return _controllerId; }
        CANT_NODISCARD const MidiControlInternal& getControl() const { return _control; }

        void update(time_m tCurrent) override = 0;

        void receiveControl(const MidiControlInternal& control);


        friend std::ostream& operator<<(std::ostream& out, const MidiController* controller);
    };

    std::ostream& operator<<(std::ostream& out, const MidiController* controller);
    std::ostream& operator<<(std::ostream& out, const UPtr<MidiController>& controller);

}

#endif //CANTINA_MIDICONTROLLER_HPP
