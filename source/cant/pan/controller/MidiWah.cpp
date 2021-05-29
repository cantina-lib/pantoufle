//
// wah!
//

#include <cant/pan/controller/MidiWah.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiWah::MidiWah(id_u8 channel, Array<id_u8, 2> wahwah)
    : MultiMidiController(channel, wahwah) {
  m_timeListener =
      std::make_shared<pattern::SelfEventListener<MidiWah, time_d>>(
          this, &MidiWah::onTimeUpdateDelta);
}

void MidiWah::onTimeUpdateDelta(CANT_MAYBEUNUSED time_d tDelta) {
  // todo
}
ShPtr<MidiController> MidiWah::wah(id_u8 channel, Array<id_u8, 2> wahwah) {
  return ShPtr<MidiController>(new MidiWah(channel, wahwah));
}

CANTINA_PAN_NAMESPACE_END
