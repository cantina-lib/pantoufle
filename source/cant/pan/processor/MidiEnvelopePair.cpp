//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopePair.hpp>

#include <cant/pan/envelope/envelope.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiEnvelopePair::
    MidiEnvelopePair(const size_u numberVoices, const id_u8 channel)
    : MidiProcessorMemory(numberVoices),
      m_toneEnvelope(FlatToneEnvelope::make(numberVoices)),
      m_velocityEnvelope(ADSREnvelope::make(numberVoices)),
      m_channel(channel)
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

CANTINA_PAN_NAMESPACE_END
