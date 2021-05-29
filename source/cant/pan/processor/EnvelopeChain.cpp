//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/EnvelopeChain.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

EnvelopeChain::EnvelopeChain(id_u8 channel)
    : m_envelopes(), m_channel(channel) {}

void EnvelopeChain::process(MidiNoteInternal &note) {
  for (auto &envelope : m_envelopes) {
    envelope->process(note);
  }
}
void EnvelopeChain::addEnvelope(UPtr<MidiEnvelope> envelope,
                                UPtr<MidiTimer> &timer) {
  envelope->subscribe(timer);
  m_envelopes.push_back(std::move(envelope));
}
void EnvelopeChain::removeEnvelope(size_u index) {
  CANTINA_ASSERT(index < m_envelopes.size(), "Nope.");
  if (index > m_envelopes.size()) {
    throw PANTOUFLE_EXCEPTION("Envelope index out of range.");
  }
  // envelope will unsubscribe on its own.
  m_envelopes.erase(m_envelopes.cbegin() + static_cast<long>(index));
}

CANTINA_PAN_NAMESPACE_END
