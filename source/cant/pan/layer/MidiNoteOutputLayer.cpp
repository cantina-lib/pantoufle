//
// Created by binabik on 21/09/2020.
//

#include <cant/pan/layer/MidiNoteOutputLayer.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiNoteOutputLayer::MidiNoteOutputLayer(size_u numberVoices)
    : m_outputNotes() {
  m_outputNotes.reserve(numberVoices);
  for (size_u i = 0; i < numberVoices; ++i) {
    m_outputNotes.emplace_back(i);
  }
}

void MidiNoteOutputLayer::receive(const MidiNoteInternal &internal) {
  m_outputNotes.at(internal.getVoice()).set(internal);
}

void MidiNoteOutputLayer::setVoice(const MidiNoteOutput &note) {
  m_outputNotes.at(note.getVoice()) = note;
}

MidiNoteOutput &MidiNoteOutputLayer::getVoiceMutable(size_u voice) {
  return m_outputNotes.at(voice);
}

const Stream<MidiNoteOutput> &MidiNoteOutputLayer::getNotes() const {
  return m_outputNotes;
}

const MidiNoteOutput &MidiNoteOutputLayer::getVoice(size_u voice) const {
  return m_outputNotes.at(voice);
}

size_u MidiNoteOutputLayer::getNumberVoices() const {
  return m_outputNotes.size();
}

CANTINA_PAN_NAMESPACE_END
