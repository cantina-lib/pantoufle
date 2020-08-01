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

namespace cant::pan
{
    class Pantoufle
    {
    private:
        MidiControllerChain _ctrlChain;
        MidiEnvelopeLayer _envlpLayer;

        Stream<MidiNoteInput> _rawNoteInput;
        Stream<MidiNoteInternal> _processedNoteInternal;
        mutable Stream<MidiNoteOutput> _processedNoteOutput;

        Map<byte_m, MidiControlInput> _rawControlInput;

        void allocateControl(byte_m controllerId);

        void processControllerChainVoice(size_m iVoice);
        void processControllerChainControl(const MidiControlInput& input);

        void processEnvelopeLayerVoice(size_m iVoice);

        void process(size_m iVoice);


        void updateRawNoteInput(time_m tCurrent);
        void updateEnvelopeLayer(const time_m tCurrent);
        void updateControlChain(time_m tCurrent);

        static time_m getCurrentTime();
    public:
        Pantoufle(size_m numberVoices, byte_m chanId);

        CANT_NODISCARD size_m getNumberVoices() const;

        void setController(UPtr<MidiController> controller);

        void receiveRawNoteData(size_m iVoice, const MidiNoteInputData& inputData);
        void receiveRawControlData(const MidiControlInputData &controlData);
        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedOutputData() const;

        void update();
    };
}

#endif //CANTINA_MIDIMACHINE_HPP
