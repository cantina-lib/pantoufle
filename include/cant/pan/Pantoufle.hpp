//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIMACHINE_HPP
#define CANTINA_MIDIMACHINE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/pan/pan_forward.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    class Pantoufle
    {
    private:
        UPtr<MidiControllerChain> _ctrlChain;
        UPtr<MidiEnvelopeLayer> _envlpLayer;

        UPtr<MidiNoteInputPoly> _poly;

        UPtr<MidiNoteInternalLayer> _processedNoteInternal;
        mutable UPtr<MidiNoteOutputLayer> _processedNoteOutput;


        UPtr<MidiTimer> _timer;

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
        void receiveRawControlData(const MidiControlData &controlData);
        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedOutputData() const;

        void update();
    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDIMACHINE_HPP
