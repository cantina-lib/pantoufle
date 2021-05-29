
#ifndef CANTINA_PAN_MIDIENVELOPE_INL
#define CANTINA_PAN_MIDIENVELOPE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

template <class Controller_T>
ShPtr<Controller_T> const &
ControlledMidiEnvelope<Controller_T>::getController() const {
  static_assert(std::is_convertible_v<Controller_T *, MidiController *>);
  return m_controller;
}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDIENVELOPE_INL