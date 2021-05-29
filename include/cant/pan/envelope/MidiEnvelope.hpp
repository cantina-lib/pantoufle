//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
#define CANTINA_PANTOUFLE_MIDIENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/controller/ControllerUpdate.hpp>
#include <cant/pan/timer/TimerUpdate.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiController;

class MidiEnvelope : public MidiProcessor, public TimerSubscribable {
public:
  /** -- methods -- **/
  void process(MidiNoteInternal &note) override = 0;

  // TimerSubscribable
  void subscribe(UPtr<MidiTimer> &) override;
  void unsubscribe(UPtr<MidiTimer> &) override;

  CANT_NODISCARD virtual ShPtr<MidiController> getController();
};

/**
 * A MidiEnvelope which uses a MidiController to process.
 * @tparam Controller_T Class of the MidiController used by the envelope.
 */
template <class Controller_T>
class ControlledMidiEnvelope : public MidiEnvelope {
  /** -- constraints -- **/
  static_assert(std::is_convertible_v<Controller_T *, MidiController *>);

public:
  /** -- methods -- **/
  CANT_NODISCARD CANT_INLINE ShPtr<MidiController> getController() final;
  CANT_INLINE void setController(UPtr<Controller_T> controller);

protected:
  ControlledMidiEnvelope();
  CANT_EXPLICIT ControlledMidiEnvelope(UPtr<Controller_T> controller);
  /**
   * Get read-only access of associated Controller from an envelope.
   */
  CANT_NODISCARD CANT_INLINE ShPtr<Controller_T> getControllerInternal() const;

private:
  // The derived envelope should not be allowed to mutate the controller!
  ShPtr<Controller_T> m_controller;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/envelope/MidiEnvelope.inl>

#endif // CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
