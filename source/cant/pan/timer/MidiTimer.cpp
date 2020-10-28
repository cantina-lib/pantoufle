//
// Created by binabik on 20/09/2020.
//

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/time/InternalClock.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiTimer::MidiTimer(UPtr<time::InternalClock> clock)
    : m_internalClock(std::move(clock)) {}

MidiTimer::MidiTimer()
    : m_internalClock(
          time::InternalClock::make(time::SystemExternalClock::make())) {}

void MidiTimer::update() {
  m_internalClock->update();
  if (this->isRunning()) {
    m_deltaTimeUpdateEvent.notify(getDeltaTime());
    m_currentTimeUpdateEvent.notify(getCurrentTime());
    m_tickEvent.notify(nullptr);
  }
}

void MidiTimer::setCustomTimeGetter(
    time::AbsoluteTimeGetter absoluteTimeGetter) {
  m_internalClock->setCustomTimeGetter(std::move(absoluteTimeGetter));
}

time_d MidiTimer::getCurrentTime() const {
  return m_internalClock->getCurrentTime();
}

time_d MidiTimer::getDeltaTime() const {
  return m_internalClock->getDeltaTime();
}

void MidiTimer::start() { m_internalClock->start(); }

void MidiTimer::stop() { m_internalClock->stop(); }

void MidiTimer::reset() { m_internalClock->reset(); }

bool MidiTimer::isRunning() const { return m_internalClock->isRunning(); }

void MidiTimer::addOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) {
  bool success = m_deltaTimeUpdateEvent.addListener(listener);
  if (!success) {
    // todo: handle error.
  }
}
void MidiTimer::addOnTimeUpdateCurrentListener(ShPtr<TimeListener> &listener) {
  bool success = m_currentTimeUpdateEvent.addListener(listener);
  if (!success) {
    // todo: handle error.
  }
}
void MidiTimer::removeOnTimeUpdateDeltaListener(ShPtr<TimeListener> &listener) {
  bool success = m_deltaTimeUpdateEvent.addListener(listener);
  if (!success) {
    // todo: handle error.
  }
}

void MidiTimer::removeOnTimeUpdateCurrentListener(
    ShPtr<TimeListener> &listener) {
  bool success = m_currentTimeUpdateEvent.removeListener(listener);
  if (!success) {
    // todo: handle error.
  }
}
void MidiTimer::addOnTickListener(ShPtr<TickListener> &listener) {
  bool success = m_tickEvent.addListener(listener);
  if (!success) {
    // todo: handle error.
  }
}
void MidiTimer::removeOnTickListener(ShPtr<TickListener> &listener) {
  bool success = m_tickEvent.removeListener(listener);
  if (!success) {
    // todo: handle error.
  }
}

CANTINA_PAN_NAMESPACE_END
