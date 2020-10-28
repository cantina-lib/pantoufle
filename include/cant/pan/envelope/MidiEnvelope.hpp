//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
#define CANTINA_PANTOUFLE_MIDIENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiEnvelope : public MidiProcessor {
public:
  /** -- methods -- **/
  // optional implementation of Listener interface
  // Is used by ADSR envelope (actually each states thereof)
  virtual void subscribe(UPtr<MidiTimer> &) {}
  virtual void unsubscribe(UPtr<MidiTimer> &) {}

  void process(MidiNoteInternal &note) override = 0;
};

class ToneEnvelope : public MidiEnvelope {
public:
  /** -- methods -- **/
  void process(MidiNoteInternal &note) override = 0;
};

class VelocityEnvelope : public MidiEnvelope {
public:
  /** -- methods -- **/
  void process(MidiNoteInternal &note) override = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
