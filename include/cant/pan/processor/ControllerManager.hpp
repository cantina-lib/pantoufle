//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_PAN_CONTROLLERMANAGER_HPP
#define CANTINA_PAN_CONTROLLERMANAGER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

// todo: make a singleton instead?
class ControllerManager {
public:
  /** -- methods -- **/
  CANT_EXPLICIT ControllerManager(size_u numberVoices);

  void addController(UPtr<MidiController> controller);

  void receiveControl(const MidiControlInternal &control);

private:
  /** -- methods -- **/
  void allocateControls(const Stream<id_u8> &controllerIds);

  /** -- fields -- **/
  size_u m_numberVoices;
  // todo: use weak pointers, controllers should be owned by envelopes.
  Stream<ShPtr<MidiController>> m_controllers;

  Map<id_u8, MidiControlInternal> m_controls;

  // constants
  static CANT_CONSTEXPR size_u c_controllerStartingSize = 50;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_CONTROLLERMANAGER_HPP
