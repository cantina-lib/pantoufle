//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PAN_PANTOUFLE_HPP
#define CANTINA_PAN_PANTOUFLE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/option.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/pan_forward.hpp>

// shouldn't have to include these....
#include <cant/pan/layer/MidiNoteInputPoly.hpp>
#include <cant/pan/layer/MidiNoteOutputLayer.hpp>
#include <cant/pan/processor/ControllerManager.hpp>
#include <cant/pan/processor/EnvelopeChain.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class Pantoufle {
public:
  /** -- methods -- **/
  Pantoufle(size_u numberVoices, id_u8 channel);

  void update();

  CANT_NODISCARD Stream<MidiNoteOutput> const &getProcessedNoteOutput() const;
  CANT_NODISCARD MidiNoteOutput const &getProcessedVoice(size_u voice) const;

  void addController(ShPtr<MidiController> controller);
  void addEnvelope(UPtr<MidiEnvelope> envelope);

  void setCustomClock(time::AbsoluteTimeGetter absoluteTimeGetter);

  Optional<size_u> receiveInputNoteData(MidiNoteInputData const &inputData);
  void receiveRawControlData(MidiControlData const &controlData);

  CANT_NODISCARD size_u getNumberVoices() const;

private:
  /** -- methods -- **/

  void process(size_u voice);
  void processControllerChainVoice(size_u voice);
  void processEnvelopePairVoice(size_u voice);
  void processAll();

  /** -- fields -- **/
  UPtr<MidiTimer> m_timer;

  UPtr<ControllerManager> m_controllerChain;
  UPtr<EnvelopeChain> m_envelopeChain;

  UPtr<MidiNoteInputPoly> m_poly;

  UPtr<MidiNoteInternalLayer> m_processedNoteInternal;

  // mutable fields
  mutable UPtr<MidiNoteOutputLayer> m_processedNoteOutput;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_PANTOUFLE_HPP
