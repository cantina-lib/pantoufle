//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopePair.hpp>

namespace cant::pan
{
    MidiEnvelopePair::
    MidiEnvelopePair(const size_u numberVoices, const id_u8 channel)
    : MidiProcessorMemory(numberVoices),
      m_toneEnvelope(FlatToneEnvelope::make(numberVoices)),
      m_velocityEnvelope(ADSREnvelope::make(numberVoices))
    {

    }

    void
    MidiEnvelopePair::
    update(time_d tCurrent)
    {
        m_toneEnvelope->update(tCurrent);
        m_velocityEnvelope->update(tCurrent);
    }

    void
    MidiEnvelopePair::
    process(MidiNoteInternal& note)
    {
        m_toneEnvelope->process(note);
        m_velocityEnvelope->process(note);
    }

    void
    MidiEnvelopePair::
    flushChange()
    {
        m_toneEnvelope->flushChange();
        m_velocityEnvelope->flushChange();
    }
}
