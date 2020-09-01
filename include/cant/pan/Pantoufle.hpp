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
    public:
        /** -- methods -- **/
        Pantoufle(size_m numberVoices, byte_m channel);

        void update();

        void setController(UPtr<MidiController> controller);
        void receiveInputNoteData(const MidiNoteInputData& inputData);
        void receiveRawControlData(const MidiControlData &controlData);

        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedOutputData() const;
        CANT_NODISCARD size_m getNumberVoices() const;
    private:
        /** -- methods -- **/
        void process(size_m iVoice);
        void processControllerChainVoice(size_m iVoice);
        void processEnvelopeLayerVoice(size_m iVoice);
        void processAll();

        void flushChange();
        void flushChangeNoteInput();
        void flushChangeEnvelopeLayer();

        void updateEnvelopeLayer(time_m tCurrent);
        void updateControlChain(time_m tCurrent);

        CANT_NODISCARD time_m getCurrentTime() const;

        /** -- fields -- **/
        UPtr<MidiControllerChain> m_controllerChain;
        UPtr<MidiEnvelopeLayer> m_envelopeLayer;

        UPtr<MidiNoteInputPoly> m_poly;

        UPtr<MidiNoteInternalLayer> m_processedNoteInternal;
        UPtr<MidiTimer> m_timer;

        // mutable fields
        mutable UPtr<MidiNoteOutputLayer> m_processedNoteOutput;
    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDIMACHINE_HPP
