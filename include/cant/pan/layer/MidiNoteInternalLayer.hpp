
#ifndef CANTINA_PAN_MIDINOTEINTERNALLAYER_HPP
#define CANTINA_PAN_MIDINOTEINTERNALLAYER_HPP

#pragma once

#include <cant/pan/layer/MidiNoteLayer.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiNoteInput;

class MidiNoteInternalLayer : MidiNoteLayerInterface<MidiNoteInternal> {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteInternalLayer(size_u numberVoices);

  void receive(const MidiNoteInput &input);
  void setVoice(const MidiNoteInternal &note);

  CANT_NODISCARD const MidiNoteInternal &getVoice(size_u voice) const final;
  CANT_NODISCARD MidiNoteInternal &getVoiceMutable(size_u voice);

  CANT_NODISCARD const Stream<MidiNoteInternal> &getNotes() const;

  CANT_NODISCARD size_u getNumberVoices() const final;

private:
  /** -- fields -- **/
  Stream<MidiNoteInternal> m_internalNotes;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDINOTEINTERNALLAYER_HPP