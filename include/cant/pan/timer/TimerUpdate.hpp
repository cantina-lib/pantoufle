
#ifndef CANTINA_PAN_TIMERUPDATE_HPP
#define CANTINA_PAN_TIMERUPDATE_HPP

#pragma once

#include <cant/common/types.hpp>

#include <cant/patterns/Event.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

typedef patterns::EventListener<time_d> TimeListener;

typedef patterns::EventListener<void *> TickListener;

typedef patterns::Event<time_d> TimeEvent;
typedef patterns::Event<void *> TickEvent;

class MidiTimer;

class TimerSubscribable {
public:
  /** -- methods -- **/
  virtual ~TimerSubscribable() = default;

  virtual void subscribe(UPtr<MidiTimer> &timer) = 0;
  virtual void unsubscribe(UPtr<MidiTimer> &timer) = 0;
};

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

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_TIMERUPDATE_HPP