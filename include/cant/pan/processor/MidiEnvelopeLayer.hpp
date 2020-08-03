//
// Created by piptouque on 28/04/2020.
//
#ifndef CANTINA_MIDIENVELOPELAYER_HPP
#define CANTINA_MIDIENVELOPELAYER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/envelope/envelope.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

namespace cant::pan
{
    class MidiEnvelopeLayer: public MidiProcessorMemory
    {
    private:
        UPtr<ToneEnvelope> _toneEnvelope;
        UPtr<VelocityEnvelope> _velocityEnvelope;
    public:

        void update(time_m tCurrent) override;
        void processVoice(size_m iVoice, MidiNoteInternal& note) override;

        CANT_EXPLICIT MidiEnvelopeLayer(size_m numberVoices, byte_m channel);

        void flushChange();

    };
}

#endif //CANTINA_MIDIENVELOPELAYER_HPP
