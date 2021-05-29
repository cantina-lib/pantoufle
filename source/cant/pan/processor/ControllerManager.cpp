//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/processor/ControllerManager.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

ControllerManager::ControllerManager(size_u numberVoices)
    : m_numberVoices(numberVoices), m_controllers(), m_controls() {
  m_controllers.reserve(c_controllerStartingSize);
}

void ControllerManager::receiveControl(MidiControlInternal const &control) {
  const id_u8 controllerId = control.getId();
  if (m_controls.find(controllerId) == m_controls.end()) {
    return;
  }
  m_controls.at(controllerId) = control;
  for (auto it = m_controllers.begin(); it < m_controllers.end();) {
    auto controller = it->lock();
    if (controller) {
      controller->receiveControl(control);
      ++it;
    } else {
      m_controllers.erase(it);
    }
  }
}

void ControllerManager::allocateControls(Stream<id_u8> const &controllerIds) {
  for (const auto &controllerId : controllerIds) {
    /*
     * In a map, attempting to inserting an already-present key
     * will not actually insert it.
     */
    m_controls.insert(std::pair<id_u8, MidiControlInternal>(
        controllerId, MidiControlInternal()));
  }
}

void ControllerManager::addController(ShPtr<MidiController> &controller) {
  allocateControls(controller->getControllerIds());
  m_controllers.push_back(controller);
}

CANTINA_PAN_NAMESPACE_END
