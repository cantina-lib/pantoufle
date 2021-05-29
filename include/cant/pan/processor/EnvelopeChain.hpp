//
// Created by piptouque on 28/04/2020.
//
#ifndef CANTINA_PAN_ENVELOPECHAIN_HPP
#define CANTINA_PAN_ENVELOPECHAIN_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>
#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiTimer;

class EnvelopeChain : public MidiProcessor {
public:
  /** -- methods -- **/
  CANT_EXPLICIT EnvelopeChain(id_u8 channel);

  void process(MidiNoteInternal &note) override;

  void addEnvelope(UPtr<MidiEnvelope> envelope, UPtr<MidiTimer> &timer);
  void removeEnvelope(size_u index);

private:
  /** -- fields -- **/
  UStream<MidiEnvelope> m_envelopes;
  id_u8 m_channel;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_ENVELOPECHAIN_HPP
