//
// Created by binabik on 05/08/2020.
//

#ifndef CANTINA_PANTOUFLE_MIDICONTROLLER_HPP
#define CANTINA_PANTOUFLE_MIDICONTROLLER_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/ControllerUpdate.hpp>

#include <cant/pan/control/control_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiController : public ControlUpdater {
public:
  /* -- methods -- */
  MidiController();

  void receiveControl(MidiControlInternal const &);
  // won't have to call it regularly, so it's fine just returning a copy
  CANT_NODISCARD virtual Stream<id_u8> getControllerIds() const = 0;

  void addOnControlReceivedListener(ShPtr<ControlListener> &) final;
  void removeOnControlReceivedListener(ShPtr<ControlListener> &) final;

private:
  /** -- methods -- **/
  virtual void impl_receiveControl(MidiControlInternal const &) = 0;

  /** -- fields -- **/
  // events (always store in shared pointers)
  ShPtr<ControlEvent> m_controlEvent;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PANTOUFLE_MIDICONTROLLER_HPP
