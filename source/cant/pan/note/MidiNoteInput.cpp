//
// Created by binabik on 21/09/2020.
//

#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/pan/timer/MidiTimer.hpp>
#include <cant/pattern/Event.hpp>

#include <iostream>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiNoteInput::MidiNoteInput(const size_u voice)
    : MidiNote<MidiNoteInputData>(voice), m_isPressed(false),
      m_justChangedPlaying(false), m_tickListener() {
  m_tickListener =
      std::make_shared<pattern::SelfEventListener<MidiNoteInput, void *>>(
          this, &MidiNoteInput::onTimerTick);
}

void MidiNoteInput::set(const time_d tCurrent, const MidiNoteInputData &data) {
  const bool wasPlaying = isPlaying();

  m_isPressed = data.isPressed();

  if (data.isPressed()) {
    if (!wasPlaying) {
      m_tStart = tCurrent;
    }
    m_data = data;
  }
  if (isPlaying() != wasPlaying) {
    m_justChangedPlaying = true;
  }
}

void MidiNoteInput::subscribe(MidiTimer &timer) {
  timer.addOnTickListener(m_tickListener);
}

void MidiNoteInput::unsubscribe(MidiTimer &timer) {
  timer.removeOnTickListener(m_tickListener);
}

void MidiNoteInput::onTimerTick(void *) {
  m_justChangedPlaying = false;
}

CANTINA_PAN_NAMESPACE_END
