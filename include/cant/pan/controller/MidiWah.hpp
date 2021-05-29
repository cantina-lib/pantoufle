//
// wah by wah on wah/wahh/waaaahhh
//

#ifndef CANTINA_PAN_WAH_HPP
#define CANTINA_PAN_WAH_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/pan/timer/TimerUpdate.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiTimer;

class MidiWah : public MultiMidiController<2>, public DeltaTimeUpdatable {
public:
  /** -- methods -- **/
  // factory method
  static ShPtr<MidiController> wah(id_u8 channel, Array<id_u8, 2> wahwah);

  void onTimeUpdateDelta(time_d tDelta) override;

private:
  /** -- methods -- **/
  MidiWah(id_u8 channel, Array<id_u8, 2> wahwah);

  /** -- fields -- **/
  ShPtr<TimeListener> m_timeListener;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // wah!
