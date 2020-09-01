//
// Created by piptouque on 28/04/2020.
//
#ifndef CANTINA_MIDIENVELOPELAYER_HPP
#define CANTINA_MIDIENVELOPELAYER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/envelope/envelope.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiEnvelopeLayer: public MidiProcessorMemory
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiEnvelopeLayer(size_m numberVoices, byte_m channel);

        void update(time_m tCurrent) override;
        void process(MidiNoteInternal& note) override;

        void flushChange();
    private:
        /** -- fields -- **/
        UPtr<ToneEnvelope> m_toneEnvelope;
        UPtr<VelocityEnvelope> m_velocityEnvelope;
    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDIENVELOPELAYER_HPP
