//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDIMACHINE_HPP
#define CANTINA_MIDIMACHINE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/common/memory.hpp>
#include <cant/common/option.hpp>

#include <cant/pan/pan_forward.hpp>

#include <cant/pan/time/time.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class Pantoufle
    {
    public:
        /** -- methods -- **/
        Pantoufle(
                size_u numberVoices,
                id_u8 channel
                );

        void update();

        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedNoteOutput() const;
        CANT_NODISCARD const MidiNoteOutput& getProcessedVoice(size_u voice) const;

        void setController(UPtr<MidiController> controller);

        void setCurrentTimeGetter(CustomMidiTimer::CurrentTimeGetter currentTimeGetter);

        Optional<size_u> receiveInputNoteData(const MidiNoteInputData& inputData);
        void             receiveRawControlData(const MidiControlData &controlData);

        CANT_NODISCARD size_u getNumberVoices() const;
    private:
        /** -- methods -- **/
        void process(size_u voice);
        void processControllerChainVoice(size_u voice);
        void processEnvelopePairVoice(size_u voice);
        void processAll();

        void flushChange();
        void flushChangeNoteInput();
        void flushChangeEnvelopePair();

        void updateTimer();
        void updateEnvelopeLayer(time_d tCurrent);
        void updateControlChain(time_d tCurrent);

        CANT_NODISCARD time_d getCurrentTime() const;

        /** -- fields -- **/
        UPtr<MidiControllerChain> m_controllerChain;
        UPtr<MidiEnvelopePair> m_envelopePair;

        UPtr<MidiNoteInputPoly> m_poly;
        UPtr<MidiTimer> m_timer;

        UPtr<MidiNoteInternalLayer> m_processedNoteInternal;

        // mutable fields
        mutable UPtr<MidiNoteOutputLayer> m_processedNoteOutput;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/Pantoufle.inl>

#endif //CANTINA_MIDIMACHINE_HPP
