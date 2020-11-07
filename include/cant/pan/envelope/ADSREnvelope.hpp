//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_PAN_ADSRENVELOPE_HPP
#define CANTINA_PAN_ADSRENVELOPE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/timer/TimerUpdate.hpp>

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/envelope/adsr_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class ADSRState;

class ADSREnvelope : private VelocityEnvelope,
                     public TimerSubscribable,
                     public DeltaTimeUpdatable,
                     public TimerTickUpdatable {
public:
  /** -- methods -- **/
  // factory method
  static UPtr<VelocityEnvelope>
  make(size_u numberVoices,
       const adsr::ArrayLengths &lengths = ADSREnvelope::c_defaultADSRLengths,
       const adsr::ArrayVelocityRatios &ratios =
           ADSREnvelope::c_defaultADSRVelocitiesRatios);
  void process(MidiNoteInternal &note) override;

  // implementation of Listener interface
  // mentioned in MidiEnvelopeModule
  void subscribe(UPtr<MidiTimer> &timer) final;
  void unsubscribe(UPtr<MidiTimer> &timer) final;

private:
  /** -- methods -- **/
  ADSREnvelope(size_u numberVoices, const adsr::ArrayLengths &lengths,
               const adsr::ArrayVelocityRatios &ratios);

  // Event functions
  void onTimeUpdateDelta(time_d tDelta) override;
  void onTimerTick(void *) override;

  // static methods
  static void checkLengths(const adsr::ArrayLengths &lengths);
  CANT_NODISCARD static bool isSustainFinite(const adsr::ArrayLengths &lengths);

  /** -- fields -- **/
  adsr::ArrayLengths m_lengths;
  adsr::ArrayVelocityRatios m_ratios;

  ShPtr<TimeListener> m_timeListener;
  ShPtr<TickListener> m_tickListener;

  Stream<ADSRState> m_states;

  // constants
  CANT_CONSTEXPR static adsr::ArrayLengths c_defaultADSRLengths = {
      30., // ADSRState::eAttack,
      -1., // ADSRState::eSustain,
      50., // ADSRState::eDecay,
      30.  // ADSRState::eRelease,
  };

  CANT_CONSTEXPR static adsr::ArrayVelocityRatios
      c_defaultADSRVelocitiesRatios = {
          1., // ADSRState::eAttack,
          0.7 // ADSRState::eSustain
      };

  /** -- friends - **/
  friend class ADSRState;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_ADSRENVELOPE_HPP
