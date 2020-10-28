//
// Created by binabik on 21/09/2020.
//

#include <cant/pan/layer/MidiNoteInternalLayer.hpp>

#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiNoteInternalLayer::MidiNoteInternalLayer(size_u numberVoices)
    : m_internalNotes() {
  m_internalNotes.reserve(numberVoices);
  for (size_u i = 0; i < numberVoices; ++i) {
    m_internalNotes.emplace_back(i);
  }
}

void MidiNoteInternalLayer::receive(const MidiNoteInput &input) {
  m_internalNotes.at(input.getVoice()).set(input);
}

void MidiNoteInternalLayer::setVoice(const MidiNoteInternal &note) {
  m_internalNotes.at(note.getVoice()) = note;
}

MidiNoteInternal &MidiNoteInternalLayer::getVoiceMutable(size_u voice) {
  return m_internalNotes.at(voice);
}

const Stream<MidiNoteInternal> &MidiNoteInternalLayer::getNotes() const {
  return m_internalNotes;
}

const MidiNoteInternal &MidiNoteInternalLayer::getVoice(size_u voice) const {
  return m_internalNotes.at(voice);
}

size_u MidiNoteInternalLayer::getNumberVoices() const {
  return m_internalNotes.size();
}

CANTINA_PAN_NAMESPACE_END
