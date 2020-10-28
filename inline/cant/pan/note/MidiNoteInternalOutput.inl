
#ifndef CANTINA_PAN_MIDINOTEINTERNALOUTPUT_INL
#define CANTINA_PAN_MIDINOTEINTERNALOUTPUT_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

CANT_INLINE
MidiNoteInternal::MidiNoteInternal(const MidiNoteInternal &other)
    : MidiNote<MidiNoteInternalData>(other), m_isPlaying(other.m_isPlaying),
      m_justChangedPlaying(other.m_justChangedPlaying) {}

CANT_INLINE
MidiNoteInternal &
MidiNoteInternal::operator=(const MidiNoteInternal &other) = default;

CANT_INLINE
time_d MidiNoteInternal::getLength(const time_d tCurrent) const {
  return tCurrent - m_tStart;
}

CANT_INLINE
void MidiNoteInternal::setPlaying(bool isPlaying) { m_isPlaying = isPlaying; }

CANT_INLINE
void MidiNoteInternal::setChangedPlaying(const bool justChanged) {
  m_justChangedPlaying = justChanged;
}

CANT_INLINE
void MidiNoteInternal::setTone(const tone_d tone) { m_data.setTone(tone); }

CANT_INLINE
void MidiNoteInternal::setVelocity(const vel_d velocity) {
  m_data.setVelocity(velocity);
}

CANT_INLINE
void MidiNoteInternal::setPan(const pan_d pan) { m_data.setPan(pan); }

CANT_INLINE
pan_d MidiNoteInternal::getPan() const { return m_data.getPan(); }

CANT_INLINE
bool MidiNoteInternal::isPlaying() const { return m_isPlaying; }

CANT_INLINE
bool MidiNoteInternal::justChangedPlaying() const {
  return m_justChangedPlaying;
}

CANT_INLINE
vel_d MidiNoteOutput::getVelocity() const { return m_data.getVelocity(); }

CANT_INLINE
vel_d MidiNoteOutput::getVelocityPlaying() const {
  return isPlaying() ? getVelocity() : static_cast<vel_d>(0);
}

CANT_INLINE
time_d MidiNoteOutput::getLength(const time_d tCurrent) const {
  return tCurrent - m_tStart;
}

CANT_INLINE
bool MidiNoteOutput::isSet() const { return m_isSet; }

CANT_INLINE
pan_d MidiNoteOutput::getPan() const { return m_data.getPan(); }

CANT_INLINE
bool MidiNoteOutput::isPlaying() const { return m_isPlaying; }

CANT_INLINE
bool MidiNoteOutput::justChangedPlaying() const { return m_justChangedPlaying; }

CANT_INLINE
bool MidiNoteOutput::justStarted() const {
  return m_justChangedPlaying && isPlaying();
}

CANT_INLINE
bool MidiNoteOutput::justStopped() const {
  return m_justChangedPlaying && !isPlaying();
}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDINOTEINTERNALOUTPUT_INL