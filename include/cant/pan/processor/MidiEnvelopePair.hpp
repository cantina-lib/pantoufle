//
// Created by piptouque on 28/04/2020.
//
#ifndef CANTINA_MIDIENVELOPELAYER_HPP
#define CANTINA_MIDIENVELOPELAYER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiEnvelopePair: public MidiProcessorMemory
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiEnvelopePair(size_u numberVoices, id_u8 channel);

        void update(time_d tCurrent) override;
        void process(MidiNoteInternal& note) override;

        void flushChange();
    private:
        /** -- fields -- **/
        UPtr<ToneEnvelope> m_toneEnvelope;
        UPtr<VelocityEnvelope> m_velocityEnvelope;
        id_u8 m_channel;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDIENVELOPELAYER_HPP
