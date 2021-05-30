
#ifndef CANTINA_PAN_TIMERUPDATE_HPP
#define CANTINA_PAN_TIMERUPDATE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/pattern/Event.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

typedef pattern::EventListener<time_d> TimeListener;

typedef pattern::EventListener<void *> TickListener;

typedef pattern::Event<time_d> TimeEvent;
typedef pattern::Event<void *> TickEvent;

class MidiTimer;

typedef pattern::EventSubscriber<MidiTimer &> TimerSubscribable;

class DeltaTimeUpdatable {
public:
  /** -- methods -- **/
  virtual ~DeltaTimeUpdatable() = default;

private:
  /** -- methods -- **/
  virtual void onTimeUpdateDelta(time_d tDelta) = 0;
};

class CurrentTimeUpdatable {
public:
  /** -- methods -- **/
  virtual ~CurrentTimeUpdatable() = default;

private:
  /** -- methods -- **/
  virtual void onTimeUpdateCurrent(time_d tCurrent) = 0;
};

/**
 * @brief The one we guarantee will be invoked exactly once
 * each time the timer is updated.
 */
class TimerTickUpdatable {
public:
  /** -- methods -- **/
  virtual ~TimerTickUpdatable() = default;

private:
  /** -- methods -- **/
  /**
   * @brief:
   * @remark: void* argument is not used. Placeholder for template class.
   */
  virtual void onTimerTick(void *) = 0;
};

class DeltaTimeUpdater {
public:
  /** -- methods -- **/
  virtual ~DeltaTimeUpdater() = default;

  virtual void addOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) = 0;

  virtual void
  removeOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) = 0;
};

class CurrentTimeUpdater {
public:
  /** -- methods -- **/
  virtual ~CurrentTimeUpdater() = default;

  virtual void
  addOnTimeUpdateCurrentListener(ShPtr<TimeListener> &listener) = 0;

  virtual void
  removeOnTimeUpdateCurrentListener(ShPtr<TimeListener> &listener) = 0;
};

class TimerTickUpdater {
public:
  /** -- methods -- **/
  virtual ~TimerTickUpdater() = default;

  virtual void addOnTickListener(ShPtr<TickListener> &listener) = 0;

  virtual void removeOnTickListener(ShPtr<TickListener> &listener) = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_TIMERUPDATE_HPP