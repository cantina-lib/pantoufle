//
// Created by binabik on 08/08/2020.
//

#include <cant/pan/controller/MidiPan.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiPan::MidiPan(id_u8 channel, id_u8 controllerId)
    : MultiMidiController<1>(channel, {controllerId}) {}

pan_d MidiPan::getPan() const {
  return (getControl(0).getValue() /
          static_cast<pan_d>(c_midiControlMidValue)) *
             2 -
         1;
}

ShPtr<MidiController> MidiPan::make(id_u8 channel, id_u8 controllerId) {
  return static_cast<ShPtr<MidiController>>(
      UPtr<MidiController>(new MidiPan(channel, controllerId)));
}

CANTINA_PAN_NAMESPACE_END