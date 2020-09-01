//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopeLayer.hpp>

namespace cant::pan
{
    MidiEnvelopeLayer::
    MidiEnvelopeLayer(const size_m numberVoices, const byte_m channel)
    : MidiProcessorMemory(numberVoices),
      m_toneEnvelope(FlatToneEnvelope::make(numberVoices)),
      m_velocityEnvelope(ADSREnvelope::make(numberVoices))
    {

    }

    void
    MidiEnvelopeLayer::
    update(time_m tCurrent)
    {
        m_toneEnvelope->update(tCurrent);
        m_velocityEnvelope->update(tCurrent);
    }

    void
    MidiEnvelopeLayer::
    process(MidiNoteInternal& note)
    {
        m_toneEnvelope->process(note);
        m_velocityEnvelope->process(note);
    }

    void
    MidiEnvelopeLayer::
    flushChange()
    {
        m_toneEnvelope->flushChange();
        m_velocityEnvelope->flushChange();
    }
}
