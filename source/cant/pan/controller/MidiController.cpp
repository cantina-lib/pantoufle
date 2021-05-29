//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/controller/MidiController.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiController::MidiController()
    : m_controlEvent(std::make_shared<ControlEvent>()) {}

void MidiController::receiveControl(MidiControlInternal const &control) {
  impl_receiveControl(control);
  m_controlEvent->invoke(control);
}
void MidiController::addOnControlReceivedListener(
    ShPtr<ControlListener> &listener) {
  m_controlEvent->addListener(listener);
}
void MidiController::removeOnControlReceivedListener(
    ShPtr<ControlListener> &listener) {
  m_controlEvent->removeListener(listener);
}

CANTINA_PAN_NAMESPACE_END
