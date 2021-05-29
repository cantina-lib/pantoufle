//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatToneEnvelope.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

UPtr<MidiEnvelope> FlatToneEnvelope::make() {
  return static_cast<UPtr<MidiEnvelope>>(
      std::unique_ptr<FlatToneEnvelope>(new FlatToneEnvelope()));
}

void FlatToneEnvelope::process(CANT_MAYBEUNUSED MidiNoteInternal &note) {
  /* nothing to doooo */
}

CANTINA_PAN_NAMESPACE_END
