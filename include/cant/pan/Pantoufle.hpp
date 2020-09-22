//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PAN_PANTOUFLE_HPP
#define CANTINA_PAN_PANTOUFLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/common/memory.hpp>
#include <cant/common/option.hpp>

#include <cant/pan/pan_forward.hpp>

// shouldn't have to include these....
#include <cant/pan/processor/MidiControllerChain.hpp>
#include <cant/pan/processor/MidiEnvelopePair.hpp>
#include <cant/pan/layer/MidiNoteInputPoly.hpp>
#include <cant/pan/layer/MidiNoteOutputLayer.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class Pantoufle
    {
    public:
        /** -- methods -- **/
        // factory method
        CANT_NODISCARD static UPtr<Pantoufle> make(size_u numberVoices, id_u8 channel);

        void update();

        CANT_NODISCARD const Stream<MidiNoteOutput>& getProcessedNoteOutput() const;
        CANT_NODISCARD const MidiNoteOutput& getProcessedVoice(size_u voice) const;

        void setController(UPtr<MidiController> controller);

        void setCustomClock(time::AbsoluteTimeGetter absoluteTimeGetter);

        Optional<size_u> receiveInputNoteData(const MidiNoteInputData& inputData);
        void             receiveRawControlData(const MidiControlData &controlData);

        CANT_NODISCARD size_u getNumberVoices() const;
    private:
        /** -- methods -- **/
        Pantoufle(
                size_u numberVoices,
                id_u8 channel
        );

        void process(size_u voice);
        void processControllerChainVoice(size_u voice);
        void processEnvelopePairVoice(size_u voice);
        void processAll();

        CANT_NODISCARD time_d getCurrentTime() const;

        /** -- fields -- **/
        UPtr<MidiTimer> m_timer;

        UPtr<MidiControllerChain> m_controllerChain;
        UPtr<MidiEnvelopePair> m_envelopePair;

        UPtr<MidiNoteInputPoly> m_poly;

        UPtr<MidiNoteInternalLayer> m_processedNoteInternal;

        // mutable fields
        mutable UPtr<MidiNoteOutputLayer> m_processedNoteOutput;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_PANTOUFLE_HPP
