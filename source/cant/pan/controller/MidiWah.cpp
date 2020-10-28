//
// wah!
//

#include <cant/pan/controller/MidiWah.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

void MidiWah::beforeControlProcess(const MidiControlInternal &) {}

void MidiWah::beforeNoteProcess(const MidiNoteInternal &) {}

MidiWah::MidiWah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah)
    : MultiMidiController(numberVoices, channel, wahwah), m_timeListener() {
  m_timeListener =
      std::make_shared<patterns::SelfEventListener<MidiWah, time_d>>(
          this, &MidiWah::onTimeUpdateDelta);
}

void MidiWah::IMPL_process(MidiNoteInternal &) const {}

void MidiWah::onTimeUpdateDelta(CANT_MAYBEUNUSED time_d tDelta) { /* todo */
}

UPtr<MidiController> MidiWah::wah(size_u numberVoices, id_u8 channel,
                                  Array<id_u8, 2> wahwah) {
  return static_cast<UPtr<MidiController>>(
      UPtr<MidiWah>(new MidiWah(numberVoices, channel, wahwah)));
}

CANTINA_PAN_NAMESPACE_END
