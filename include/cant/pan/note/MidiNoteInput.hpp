
#ifndef CANTINA_PAN_MIDINOTEINPUT_HPP
#define CANTINA_PAN_MIDINOTEINPUT_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/timer/TimerUpdate.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiTimer;

class MidiNoteInput : public MidiNote<MidiNoteInputData>,
                      public MidiNoteInputCompatible,
                      public TimerTickUpdatable,
                      public TimerSubscribable {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteInput(size_u voice);

  void set(time_d tCurrent, const MidiNoteInputData &data);

  CANT_NODISCARD bool isPlaying() const override;
  CANT_NODISCARD bool justChangedPlaying() const override;

  CANT_NODISCARD tone_i8 getToneNative() const;
  CANT_NODISCARD vel_i8 getVelocityNative() const;

  void subscribe(MidiTimer &timer) override;
  void unsubscribe(MidiTimer &timer) override;

private:
  /** -- methods -- **/
  void onTimerTick(void *) override;

  /** -- fields -- **/
  bool m_isPressed;

  bool m_justChangedPlaying;

  ShPtr<TickListener> m_tickListener;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/note/MidiNoteInput.inl>

#endif // CANTINA_PAN_MIDINOTEINPUT_HPP