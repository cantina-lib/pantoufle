//
// Created by piptouque on 28/04/2020.
//
#ifndef CANTINA_MIDIENVELOPELAYER_HPP
#define CANTINA_MIDIENVELOPELAYER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/envelope/envelope.hpp>

#include <cant/pan/stream/MidiStream.hpp>
#include <cant/pan/processor/MidiProcessor.hpp>



namespace cant::pan
{
    class MidiEnvelopeLayer: public MidiProcessorMemory
    {
    private:
        void allocateProcessed(const UPtr<ToneEnvelope>& toneEnvelope, const UPtr<VelocityEnvelope>& velocityEnvelope);
    public:
        void processVoice(sizeint iVoice, const UPtr<MidiNote>& note) override;

        CANT_EXPLICIT MidiEnvelopeLayer(sizeint numberVoices, byte_m chanId);

    };
}

#endif //CANTINA_MIDIENVELOPELAYER_HPP
