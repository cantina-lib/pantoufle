
#ifndef CANTINA_PAN_MIDIENVELOPE_INL
#define CANTINA_PAN_MIDIENVELOPE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

template <class Controller_T>
ControlledMidiEnvelope<Controller_T>::ControlledMidiEnvelope(
    UPtr<Controller_T> controller) {
  setController(std::move(controller));
}
template <class Controller_T>
ControlledMidiEnvelope<Controller_T>::ControlledMidiEnvelope() = default;

template <class Controller_T>
CANT_INLINE ShPtr<Controller_T>
ControlledMidiEnvelope<Controller_T>::getControllerInternal() const {
  return m_controller;
}

template <class Controller_T>
CANT_INLINE ShPtr<MidiController>
ControlledMidiEnvelope<Controller_T>::getController() {
  return m_controller;
}

template <class Controller_T>
CANT_INLINE void ControlledMidiEnvelope<Controller_T>::setController(
    UPtr<Controller_T> controller) {
  m_controller = std::move(controller);
}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDIENVELOPE_INL