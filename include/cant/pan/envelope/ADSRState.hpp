
#ifndef CANTINA_PAN_ADSRSTATE_HPP
#define CANTINA_PAN_ADSRSTATE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pattern/Slider.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/pan/envelope/adsr_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class ADSRState {
public:
  /** -- typedefs -- **/
  typedef pattern::Slider<vel_d, time_d> VelSlider;

  /** -- internal structures -- **/
  enum ADSRStateType {
    eAttack = 0, // he attac
    eDecay = 2,  // he decay
    // but most importantly
    eSustain = 1, // he won't throw sustain away
    eRelease = 3,
    eNotPlaying = 4
  };

  /** -- methods -- **/
  /**
   * Should only be constructed by the envelope it is owned by.
   */
  CANT_EXPLICIT ADSRState(size_u voice);

  void updateTypeLength(ADSREnvelope const *env, time_d tDelta);
  /**
   * Update the state from a received note.
   * @param env
   * @param note
   */
  void update(ADSREnvelope const *env, MidiNoteInternal const &note);
  /**
   * Update the state from a received control.
   * @param env
   * @param control
   */
  void onControllerChange(ADSREnvelope const *env);

  void apply(MidiNoteInternal &note) const;

  CANT_NODISCARD ADSRStateType getType() const;
  CANT_NODISCARD time_d getLength() const;

private:
  /** -- methods -- **/

  CANT_NODISCARD type_d getVelocityRatio() const;

  void setType(const ADSREnvelope *env, ADSRStateType type, time_d length);
  void setTypeLengthManual(ADSREnvelope const * env, ADSRStateType type);

  CANT_NODISCARD bool justChangedPlaying() const;
  void raiseFlagChangedPlaying();
  void discardFlagChangedPlaying();

  CANT_NODISCARD bool isPlaying() const;

  // static methods
  static void computeTypeLengthRecursive(ADSRStateType &type, time_d &length,
                                         adsr::ArrayLengths const & lengths);

  /**
   * @param ratios
   * @return actual velocity ratio for current type (will be null if not playing)
   */
  CANT_NODISCARD type_d
  getTypeTargetVelocityRatio(adsr::ArrayVelocityRatios const & ratios) const;

  /**
   * @param lengths
   * @return actual length for current type (will be null if not playing)
   */
  CANT_NODISCARD type_d
  getTypeTargetSlidingTime(adsr::ArrayLengths const & lengths) const;

  /** -- fields -- **/
  ADSRStateType m_type;
  time_d m_length;

  VelSlider m_velocitySlider;

  bool m_flagJustChangedPlaying;

  MidiNoteInternal m_noteCached;

  /** -- constants -- **/
  static CANT_CONSTEXPR time_d c_slidingTime = 100; // in milliseconds.

  /** -- friends -- **/
  friend class ADSREnvelope;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/envelope/ADSRState.inl>

#endif // CANTINA_PAN_ADSRSTATE_HPP