
#ifndef CANTINA_PAN_ADSRSTATE_INL
#define CANTINA_PAN_ADSRSTATE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


CANT_INLINE
bool ADSRState::justChangedPlaying() const { return m_flagJustChangedPlaying; }

CANT_INLINE
void ADSRState::raiseFlagChangedPlaying() { m_flagJustChangedPlaying = true; }

CANT_INLINE
void ADSRState::discardFlagChangedPlaying() { m_flagJustChangedPlaying = false; }

CANT_INLINE
type_d ADSRState::getVelocityRatio() const {
  return m_velocitySlider.getValue();
}

CANT_INLINE
time_d ADSRState::getLength() const { return m_length; }

CANT_INLINE
ADSRState::ADSRStateType ADSRState::getType() const { return m_type; }

CANT_INLINE
bool ADSRState::isPlaying() const {
  return m_type != ADSRStateType::eNotPlaying;
}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_ADSRSTATE_INL