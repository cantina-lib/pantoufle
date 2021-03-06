//
// Created by binabik on 05/06/2020.
//

#include <cant/pan/controller/MidiDamper.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiDamper::MidiDamper(id_u8 channel, id_u8 controllerId)
    : MultiMidiController<1>(channel, {controllerId}) {}

bool MidiDamper::isOn() const { return isOn(getControl(0)); }

bool MidiDamper::isOn(MidiControlInternal const &control) {
  return control.getValue() > c_midiControlMidValue;
}

UPtr<MidiDamper> MidiDamper::make(id_u8 channel, id_u8 controllerId) {
  return std::make_unique<MidiDamper>(channel, controllerId);
}

CANTINA_PAN_NAMESPACE_END