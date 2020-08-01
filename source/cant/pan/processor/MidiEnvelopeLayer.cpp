//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopeLayer.hpp>

#include <fmt/format.h>

namespace cant::pan
{
    MidiEnvelopeLayer::
    MidiEnvelopeLayer(const size_m numberVoices, const byte_m channel)
    : MidiProcessorMemory(numberVoices),
    _toneEnvelope(FlatToneEnvelope::make()),
    _velocityEnvelope(ADSREnvelope::make())
    {

    }

    void
    MidiEnvelopeLayer::
    update(time_m tCurrent)
    {
        _tCurrent = tCurrent;
    }

    void
    MidiEnvelopeLayer::
    processVoice(const size_m iVoice, MidiNoteInternal& note)
    {

    }
}
