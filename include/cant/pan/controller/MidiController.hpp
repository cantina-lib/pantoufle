//
// Created by binabik on 05/08/2020.
//

#ifndef CANTINA_TILDE_MIDICONTROLLER_HPP
#define CANTINA_TILDE_MIDICONTROLLER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessorMemory.hpp>

#include <cant/pan/control/control_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiController : public MidiProcessorMemory {
public:
  /* -- methods -- */
  void process(MidiNoteInternal &internal) final;
  void receiveControl(const MidiControlInternal &control);
  // won't have to call it regularly, so it's fine just returning a copy
  CANT_NODISCARD virtual Stream<id_u8> getControllerIds() const = 0;

protected:
  /** -- methods -- **/
  CANT_EXPLICIT MidiController(size_u numberVoices);
  // event functions
  virtual void beforeControlProcess(const MidiControlInternal &control) = 0;
  /**
   * State changes in the controller as side-effects should be called here.
   * Controller will not be allowed to mutate in IMPL_processVoice,
   * but will be automatically updated in updateDelta.
   **/
  virtual void beforeNoteProcess(const MidiNoteInternal &note) = 0;

private:
  /** -- methods -- **/
  void updateVoice(const MidiNoteInternal &note);
  // private inheritance
  virtual void IMPL_receiveControl(const MidiControlInternal &control) = 0;
  virtual void IMPL_process(MidiNoteInternal &note) const = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_TILDE_MIDICONTROLLER_HPP
