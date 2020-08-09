//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIMACHINE_HPP
#define CANTINA_MIDIMACHINE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/pan/common/MidiTimer.hpp>

#include <cant/pan/controller/MidiController.hpp>
#include <cant/pan/processor/MidiControllerChain.hpp>
#include <cant/pan/processor/MidiEnvelopeLayer.hpp>

#include <cant/pan/layer/MidiNoteInputPoly.hpp>


#include <cant/pan/control/control.hpp>
#include <cant/pan/note/note.hpp>

namespace cant::pan
{
    class Pantoufle
    {
    private:
        MidiControllerChain _ctrlChain;
        MidiEnvelopeLayer _envlpLayer;

        MidiNoteInputPoly _poly;

        MidiNoteInternalLayer _processedNoteInternal;
        mutable MidiNoteOutputLayer _processedNoteOutput;


        MidiTimer _timer;

        void processControllerChainVoice(size_m iVoice);

        void processEnvelopeLayerVoice(size_m iVoice);

        void process(size_m iVoice);

        void flushChangeNoteInput();
        void flushChangeEnvelopeLayer();

        void flushChange();



        void updateEnvelopeLayer(time_m tCurrent);
        void updateControlChain(time_m tCurrent);
        void processAll();

        CANT_NODISCARD time_m getCurrentTime() const;
    public:
        Pantoufle(size_m numberVoices, byte_m channel);

        CANT_NODISCARD size_m getNumberVoices() const;

        void setController(UPtr<MidiController> controller);

        void receiveInputNoteData(const MidiNoteInputData& inputData);
        void receiveRawControlData(const MidiControlInputData &controlData);
        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedOutputData() const;

        void update();
    };
}

#endif //CANTINA_MIDIMACHINE_HPP
