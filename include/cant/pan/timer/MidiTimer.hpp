
#ifndef PANTOUFLE_MIDITIMER_HPP
#define PANTOUFLE_MIDITIMER_HPP

#pragma once

#include <cant/time/common/types.hpp>

#include <cant/pan/timer/TimerUpdate.hpp>

#include <cant/time/InternalClock.hpp>

#include <cant/common/macro.hpp>
// Forward declaration of InternalClock in cant::time
// can't do it inside pan because it will then be in cant::pan::time.
// Reason is that with std::unique_ptr's, the type have to be complete.
// this wouldn't be the case if we were using raw pointer.
// but we won't.
/**
 * This s don't work, yo.
CANTINA_TIME_NAMESPACE_BEGIN
class InternalClock;
CANTINA_TIME_NAMESPACE_END
 */

CANTINA_PAN_NAMESPACE_BEGIN
class MidiTimer : public DeltaTimeUpdater,
                  public CurrentTimeUpdater,
                  public TimerTickUpdater {
public:
  /** -- typedefs -- **/
  typedef ::cant::time::AbsoluteTimeGetter TimeGetter;

  /** -- methods -- **/
  /**
   * @brief Construct a MidiTimer from a type of ExternalClock.
   * @tparam ExternalClock_T : A child class of time::ExternalClock.
   */
  CANT_EXPLICIT MidiTimer(UPtr<time::InternalClock> clock);
  MidiTimer();

  CANT_NODISCARD time_d getCurrentTime() const;
  CANT_NODISCARD time_d getDeltaTime() const;

  void setCustomTimeGetter(TimeGetter absoluteTimeGetter);

  void start();
  void stop();
  void update();
  void reset();

  CANT_NODISCARD bool isRunning() const;

  void addOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) final;
  void addOnTimeUpdateCurrentListener(ShPtr<TimeListener> &listener) final;
  void addOnTickListener(ShPtr<TickListener> &listener) final;

  void removeOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) final;
  void removeOnTimeUpdateCurrentListener(ShPtr<TimeListener> &listener) final;
  void removeOnTickListener(ShPtr<TickListener> &listener) final;

private:
  /** -- fields -- **/
  UPtr<time::InternalClock> m_internalClock;

  // events (should be stored in shared pointers).
  ShPtr<TimeEvent> m_deltaTimeUpdateEvent;
  ShPtr<TimeEvent> m_currentTimeUpdateEvent;
  ShPtr<TickEvent> m_tickEvent;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // PANTOUFLE_MIDITIMER_HPP