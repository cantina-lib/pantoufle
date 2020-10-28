
#ifndef CANTINA_PAN_MIDINOTEOUTPUTLAYER_HPP
#define CANTINA_PAN_MIDINOTEOUTPUTLAYER_HPP

#pragma once

#include <cant/pan/layer/MidiNoteLayer.hpp>
#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiNoteInternal;

class MidiNoteOutputLayer : MidiNoteLayerInterface<MidiNoteOutput> {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteOutputLayer(size_u numberVoices);

  void receive(const MidiNoteInternal &internal);
  void setVoice(const MidiNoteOutput &output);

  CANT_NODISCARD const MidiNoteOutput &getVoice(size_u voice) const final;
  CANT_NODISCARD MidiNoteOutput &getVoiceMutable(size_u voice);

  CANT_NODISCARD const Stream<MidiNoteOutput> &getNotes() const;

  CANT_NODISCARD size_u getNumberVoices() const final;

private:
  /** -- fields -- **/
  Stream<MidiNoteOutput> m_outputNotes;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDINOTEOUTPUTLAYER_HPP