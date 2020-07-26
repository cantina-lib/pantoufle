//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDICONTROLPROCESSOR_HPP
#define CANTINA_MIDICONTROLPROCESSOR_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/note/ControlledMidiNote.hpp>
#include <cant/pan/control/MidiControl.hpp>
#include <cant/pan/controller/MidiController.hpp>

#include <cant/pan/stream/MidiStream.hpp>

namespace cant::midi
{
    class MidiControllerChain final : public MidiProcessorMemory
    {
    private:
        UMap<byte_m, MidiController> _controllers;
    private:
        void processVoiceChained(sizeint iVoice, const UPtr <MidiNote> &in);
        CANT_NODISCARD const UPtr<MidiNote>& getProcessedVoiceChained(sizeint iVoice) const;

        void allocatedProcessed();
    public:
        void processVoice(sizeint iVoice, const UPtr<MidiNote>& in) override;

        CANT_EXPLICIT MidiControllerChain(sizeint numberVoices);

        void setController(UPtr<MidiController> controller);
        void processControl(const MidiControlInput& input, const UStream<MidiNote>& inStream);

        void update(time_m tCurrent) override;

    };
}

#endif //CANTINA_MIDICONTROLPROCESSOR_HPP
