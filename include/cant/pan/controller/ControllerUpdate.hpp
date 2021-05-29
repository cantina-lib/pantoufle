
#ifndef CANTINA_PAN_CONTROLLERUPDATE_HPP
#define CANTINA_PAN_CONTROLLERUPDATE_HPP

#pragma once

#include <cant/pattern/Event.hpp>

#include <cant/pan/control/MidiControlData.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

typedef pattern::EventListener<MidiControlInternal const &> ControlListener;

typedef pattern::Event<MidiControlInternal const &> ControlEvent;

class MidiController;

/**
 * @brief: An interface for class whose internal mechanics
 * involve updating from Control events.
 * Basically these classes will aggregate ControlUpdatable etc.
 */
typedef pattern::EventSubscriber<ShPtr<MidiController>> ControllerSubscribable;

/**
 * An interface for classes that are directly updated by a Control Received
 * event.
 */
class ControlUpdatable {
public:
  /** -- methods -- **/
  virtual ~ControlUpdatable() = default;

private:
  /** -- methods -- **/
  virtual void onControlReceived(MidiControlInternal const &control) = 0;
};

/**
 * @brief: An interface for class that will update listeners
 * of the onControlReceived event. For instance, MidiController.
 */
class ControlUpdater {
public:
  /** -- methods -- **/
  virtual ~ControlUpdater() = default;

  virtual void
  addOnControlReceivedListener(ShPtr<ControlListener> &listener) = 0;
  virtual void
  removeOnControlReceivedListener(ShPtr<ControlListener> &listener) = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_CONTROLLERUPDATE_HPP