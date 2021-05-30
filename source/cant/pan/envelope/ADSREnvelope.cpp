//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>
#include <cant/pan/envelope/ADSRState.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

UPtr<ADSREnvelope> ADSREnvelope::make(size_u numberVoices,
                                      adsr::ArrayLengths const &lengths,
                                      adsr::ArrayVelocityRatios const &ratios) {
  return UPtr<ADSREnvelope>(new ADSREnvelope(numberVoices, lengths, ratios));
}

ADSREnvelope::ADSREnvelope(size_u numberVoices,
                           adsr::ArrayLengths const &lengths,
                           adsr::ArrayVelocityRatios const &ratios)
    : ControlledMidiEnvelope<MidiDamper>(), m_lengths(lengths),
      m_ratios(ratios), m_states() {
  checkLengths(m_lengths);
  m_states.reserve(numberVoices);
  for (size_u voice = 0; voice < numberVoices; ++voice) {
    m_states.emplace_back(voice);
  }
  m_controlListener = std::make_shared<
      pattern::SelfEventListener<ADSREnvelope, MidiControlInternal const &>>(
      this, &ADSREnvelope::onControlReceived);
  m_timeListener =
      std::make_shared<pattern::SelfEventListener<ADSREnvelope, time_d>>(
          this, &ADSREnvelope::onTimeUpdateDelta);
  m_tickListener =
      std::make_shared<pattern::SelfEventListener<ADSREnvelope, void *>>(
          this, &ADSREnvelope::onTimerTick);
}

void ADSREnvelope::checkLengths(const adsr::ArrayLengths &lengths) {
  if ((lengths.at(ADSRState::eAttack) < static_cast<time_d>(0.)) ||
      (lengths.at(ADSRState::eDecay) < static_cast<time_d>(0.)) ||
      (lengths.at(ADSRState::eRelease) < static_cast<time_d>(0.))) {
    // todo: better error message.
    throw PANTOUFLE_EXCEPTION("noooooo");
  }
}

bool ADSREnvelope::isSustainFinite(const adsr::ArrayLengths &lengths) {
  return lengths.at(ADSRState::ADSRStateType::eSustain) >=
         static_cast<time_d>(0.);
}


void ADSREnvelope::onTimeUpdateDelta(time_d tDelta) {
  // update type and length of states
  for (auto &state : m_states) {
    state.updateTypeLength(this, tDelta);
  }
}

void ADSREnvelope::process(MidiNoteInternal &note) {
  /*
   * There used to be a concept of 'extendability'
   * where a note could be extended by the envelope or not
   * now assuming every note is extendable.
   */
  ADSRState &state = m_states.at(note.getVoice());
  state.update(this, note);
  state.apply(note);
}

void ADSREnvelope::subscribe(MidiTimer &timer) {
  timer.addOnTimeUpdateDeltaListener(m_timeListener);
  timer.addOnTickListener(m_tickListener);
}

void ADSREnvelope::unsubscribe(MidiTimer &timer) {
  timer.removeOnTimeUpdateDeltaListener(m_timeListener);
  timer.removeOnTickListener(m_tickListener);
}

void ADSREnvelope::onTimerTick(void *) {
  for (auto &state : m_states) {
    state.discardFlagChangedPlaying();
  }
}

void ADSREnvelope::onControlReceived(
    CANT_MAYBEUNUSED MidiControlInternal const &control) {
  // we don't actually update from the control, but from the internal
  // controller.
  for (auto &state : m_states) {
    state.onControllerChange(this);
  }
}

void ADSREnvelope::subscribeController(MidiController &controller) {
  controller.addOnControlReceivedListener(m_controlListener);
}
void ADSREnvelope::unsubscribeController(MidiController &controller) {
  controller.removeOnControlReceivedListener(m_controlListener);
}

CANTINA_PAN_NAMESPACE_END
