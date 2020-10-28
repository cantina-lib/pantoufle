//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopePair.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/pan/envelope/envelope.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiEnvelopePair::MidiEnvelopePair(size_u numberVoices, id_u8 channel,
                                   UPtr<MidiTimer> &timer)
    : m_toneEnvelope(FlatToneEnvelope::make()),
      m_velocityEnvelope(ADSREnvelope::make(numberVoices)), m_channel(channel) {
  m_toneEnvelope->subscribe(timer);
  m_velocityEnvelope->subscribe(timer);
}

void MidiEnvelopePair::process(MidiNoteInternal &note) {
  m_toneEnvelope->process(note);
  m_velocityEnvelope->process(note);
}

CANTINA_PAN_NAMESPACE_END
