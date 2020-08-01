//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopeLayer.hpp>

#include <fmt/format.h>

namespace cant::pan
{
    MidiEnvelopeLayer::
    MidiEnvelopeLayer(const sizeint numberVoices, const byte_m chanId)
    : MidiProcessorMemory(numberVoices)
    {
        allocateProcessed(FlatToneEnvelope::make(), ADSREnvelope::make());
    }

    void
    MidiEnvelopeLayer::
    allocateProcessed(const UPtr<ToneEnvelope>& toneEnvelope, const UPtr<VelocityEnvelope>& velocityEnvelope)
    {
        for(auto& envNote : _processed)
        {
            envNote = UPtr<EnvelopedMidiNote>(new EnvelopedMidiNote(toneEnvelope, velocityEnvelope));
        }
    }

    void
    MidiEnvelopeLayer::
    processVoice(const sizeint iVoice, const UPtr<MidiNote>& note)
    {
        if(!MidiNote::isNoteSet(note))
        {
            throw PANTOUFLE_EXCEPTION("Received note not set.");
        }
        auto& envNote = _processed.at(iVoice);
        PANTOUFLE_TRY_RETHROW({
             envNote->updateElseSet(note);
        })
    }
}
