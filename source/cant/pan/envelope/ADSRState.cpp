//
// Created by binabik on 22/09/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>
#include <cant/pan/envelope/ADSRState.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

ADSRState::ADSRState(size_u voice)
    : m_type(ADSRStateType::eNotPlaying), m_length(),
      m_velocitySlider(maths::approx<vel_d>::barycentre<type_d>),
      m_flagJustChangedPlaying(false), m_noteCached(voice) {}

void ADSRState::update(ADSREnvelope const *env, MidiNoteInternal const &note) {
  if (note.justChangedPlaying()) {
    // Damper override the playing state of the note if on.
    if (note.isPlaying()) {
      setTypeLengthManual(env, ADSRStateType::eAttack);
    } else if (!env->getInternalController()->isOn()) {
      setTypeLengthManual(env, ADSRStateType::eRelease);
    }
  }
  m_noteCached = note;
}

void ADSRState::onControllerChange(ADSREnvelope const *env) {
  if (!env->getInternalController()->isOn() && !m_noteCached.isPlaying()) {
    // Damper is released, resuming normal envelope.
    setTypeLengthManual(env, ADSRStateType::eRelease);
  }
}

void ADSRState::setTypeLengthManual(ADSREnvelope const *env,
                                    ADSRStateType type) {
  setType(env, type, 0.);
}

void ADSRState::updateTypeLength(ADSREnvelope const *env, time_d tDelta) {
  // starting values.
  ADSRStateType type = m_type;
  time_d length = getLength() + tDelta;

  // recursively computing updated type and length.
  computeTypeLengthRecursive(type, length, env->m_lengths);
  setType(env, type, length);

  m_velocitySlider.updateDelta(tDelta);
}

void ADSRState::setType(const ADSREnvelope *env, ADSRStateType type,
                        time_d length) {
  const bool wasPlaying = isPlaying();
  const bool justChangedType = type != getType();

  m_type = type;
  m_length = length;

  const bool justChangedPlaying = wasPlaying != isPlaying();

  if (justChangedPlaying) {
    raiseFlagChangedPlaying();
  }
  if (justChangedType) {
    m_velocitySlider.setTarget(getTypeTargetVelocityRatio(env->m_ratios),
                               getTypeTargetSlidingTime(env->m_lengths));
  }
}

void ADSRState::computeTypeLengthRecursive(ADSRStateType &type, time_d &length,
                                           const adsr::ArrayLengths &lengths) {
  switch (type) {
  case ADSRStateType::eAttack:
    if (length >= lengths.at(eAttack)) {
      type = ADSRStateType::eDecay;
      length -= lengths.at(eAttack);
      break;
    }
    return;
  case ADSRStateType::eDecay:
    if (length >= lengths.at(eDecay)) {
      type = ADSRStateType::eSustain;
      length -= lengths.at(eDecay);
      break;
    }
    return;
  case ADSRStateType::eSustain:
    if (ADSREnvelope::isSustainFinite(lengths) &&
        (length > lengths.at(eSustain))) {
      type = ADSRStateType::eRelease;
      length -= lengths.at(eSustain);
      break;
    }
    return;
  case ADSRStateType::eRelease:
    if (length >= lengths.at(eRelease)) {
      type = ADSRStateType::eNotPlaying;
      length -= lengths.at(eRelease);
      break;
    }
    return;
  case ADSRStateType::eNotPlaying:
    // nothing to do.
    return;
  }
  computeTypeLengthRecursive(type, length, lengths);
}

void ADSRState::apply(MidiNoteInternal &note) const {
  const type_d velocityRatio = getVelocityRatio();
  note.setVelocity(note.getVelocity() * velocityRatio);
  note.setPlaying(this->isPlaying());
  note.setChangedPlaying(this->justChangedPlaying());
}

type_d ADSRState::getTypeTargetVelocityRatio(
    const adsr::ArrayVelocityRatios &ratios) const {
  auto ratio = static_cast<type_d>(0.);
  switch (getType()) {
  case ADSRStateType::eAttack:
    ratio = ratios.at(ADSRStateType::eAttack);
    break;
  case ADSRStateType::eDecay:
  case ADSRStateType::eSustain:
    ratio = ratios.at(ADSRStateType::eSustain);
    break;
  case ADSRStateType::eRelease:
  case ADSRStateType::eNotPlaying:
    break;
  }
  return ratio;
}

type_d
ADSRState::getTypeTargetSlidingTime(adsr::ArrayLengths const & lengths) const {
  ADSRStateType const refType = getType() == ADSRStateType::eNotPlaying
      ? ADSRStateType::eDecay
      : getType();
  return lengths.at(refType);
}


CANTINA_PAN_NAMESPACE_END
