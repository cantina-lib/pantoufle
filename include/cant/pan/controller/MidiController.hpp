//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControl.hpp>
#include <cant/pan/note/ControlledMidiNote.hpp>

#include <cant/pan/stream/MidiStream.hpp>


namespace cant::midi
{

    /**
     * IMPORTANT
     * MidiController should never reallocate _control
     * because ControlledMidiNotes will have weak ref to it
     * We should reset the underlying pointer instead
     **/
    class MidiController : public MidiProcessorMemoryProxy<ControlledMidiNote>
    {
    private:
        byte_m _channel;
        const byte_m _controllerId; // todo: should be static? Damper -> 110 (ex)... NAH
        ShPtr<MidiControl> _control;

    private:
        CANT_NODISCARD virtual UPtr<ControlledMidiNote> allocateNote(const WPtr <MidiControl> &control) const = 0;

    private:
        CANT_NODISCARD const ShPtr<MidiControl>& getControlShared() const;
        CANT_NODISCARD WPtr<MidiControl> getControlWeak() const;

        CANT_NODISCARD static bool isControllerSet(const MidiController* controller);

        void notifyProcessedOnChange();
    protected:
        void allocateProcessed();

        CANT_NODISCARD bool isSet() const;
        CANT_NODISCARD bool isControlSet() const;


        CANT_EXPLICIT MidiController(sizeint numberVoices, byte_m channel, byte_m controllerId);
    public:
        void processVoice(sizeint iVoice, const UPtr<MidiNote>& in) final;

        CANT_NODISCARD static bool isControllerSet(const UPtr<MidiController>& controller);


        CANT_NODISCARD byte_m getControllerId() const { return _controllerId; }
        void receiveControl(const MidiControlInput& input);


        void processVoiceChained(sizeint iVoice, const UPtr<MidiController> &source);


        friend std::ostream& operator<<(std::ostream& out, const MidiController* controller);
    };

    std::ostream& operator<<(std::ostream& out, const MidiController* controller);
    std::ostream& operator<<(std::ostream& out, const UPtr<MidiController>& controller);

}

#endif //CANTINA_MIDICONTROLLER_HPP
