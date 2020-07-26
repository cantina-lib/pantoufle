//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIMACHINE_HPP
#define CANTINA_MIDIMACHINE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/pan/common/Time.hpp>

#include <cant/pan/processor/processor.hpp>

#include <cant/pan/control/control.hpp>
#include <cant/pan/note/note.hpp>

#include <cant/pan/stream/MidiStream.hpp>

namespace cant::midi
{
    class MidiMachine
    {
    private:
        MidiControllerChain _ctrlChain;
        MidiEnvelopeLayer _envlpLayer;

        Stream<MidiNoteInput> _rawNoteInput;
        UStream<MidiNote> _rawNotes;
        mutable Stream<MidiNoteOutput> _processedNoteOutput;

        Map<byte_m, MidiControlInput> _rawControlInput;

        void allocateControl(byte_m controllerId);

        void processControllerChainVoice(sizeint iVoice);
        void processControllerChainControl(const MidiControlInput& input);

        void processEnvelopeLayerVoice(sizeint iVoice);

        void process(sizeint iVoice);


        void updateRawNotes();
        void updateEnvelopes();
        void updateControlChain();

        static time_m getCurrentTime();
    public:
        MidiMachine(sizeint numberVoices, byte_m chanId);

        CANT_NODISCARD sizeint getNumberVoices() const;

        void setController(UPtr<MidiController> controller);

        void receiveRawNoteData(sizeint iVoice, const MidiNoteInputData& noteData);
        void receiveRawControlData(const MidiControlInputData &controlData);
        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedOutputData() const;

        void update();
    };
}

#endif //CANTINA_MIDIMACHINE_HPP
