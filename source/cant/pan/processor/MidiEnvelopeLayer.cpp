//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopeLayer.hpp>

namespace cant::pan
{
    MidiEnvelopeLayer::
    MidiEnvelopeLayer(const size_m numberVoices, const byte_m channel)
    : MidiProcessorMemory(numberVoices),
    _toneEnvelope(FlatToneEnvelope::make(numberVoices)),
    _velocityEnvelope(ADSREnvelope::make(numberVoices))
    {

    }

    void
    MidiEnvelopeLayer::
    update(time_m tCurrent)
    {
        _toneEnvelope->update(tCurrent);
        _velocityEnvelope->update(tCurrent);
    }

    void
    MidiEnvelopeLayer::
    processVoice(const size_m iVoice, MidiNoteInternal& note)
    {
        _toneEnvelope->processVoice(iVoice, note);
        _velocityEnvelope->processVoice(iVoice, note);
    }

    void
    MidiEnvelopeLayer::
    flushChange()
    {
        _toneEnvelope->flushChange();
        _velocityEnvelope->flushChange();
    }
}
