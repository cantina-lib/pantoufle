//
// Created by piptouque on 30/04/2020.
//
#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

void cant::pan::MidiEnvelope::subscribe(cant::UPtr<cant::pan::MidiTimer> &) {}
void MidiEnvelope::unsubscribe(UPtr<MidiTimer> &) {}
ShPtr<MidiController> MidiEnvelope::getController() {
  return ShPtr<MidiController>();
}

CANTINA_PAN_NAMESPACE_END
