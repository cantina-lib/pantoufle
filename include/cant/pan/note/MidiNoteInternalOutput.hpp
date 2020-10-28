
#ifndef CANTINA_PAN_MIDINOTEINTERNALOUTPUT_HPP
#define CANTINA_PAN_MIDINOTEINTERNALOUTPUT_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiNoteInput;

class MidiNoteInternal : public MidiNote<MidiNoteInternalData>,
                         public MidiNoteInternalCompatible {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteInternal(size_u voice);
  MidiNoteInternal(const MidiNoteInternal &other);
  MidiNoteInternal &operator=(const MidiNoteInternal &other);

  void set(const MidiNoteInput &input);

  CANT_NODISCARD time_d getLength(time_d tCurrent) const override;

  void setPlaying(bool isPlaying);
  void setChangedPlaying(bool justChanged);

  void setTone(tone_d tone) override;
  void setVelocity(vel_d velocity) override;
  void setPan(pan_d pan) override;

  CANT_NODISCARD pan_d getPan() const override;

  CANT_NODISCARD bool isPlaying() const override;
  CANT_NODISCARD bool justChangedPlaying() const override;

private:
  /** -- fields -- **/
  bool m_isPlaying;
  bool m_justChangedPlaying;
};

class MidiNoteOutput : public MidiNote<MidiNoteOutputData>,
                       public MidiNoteOutputCompatible {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteOutput(size_u voice);

  void set(const MidiNoteInternal &internal);

  CANT_NODISCARD time_d getLength(time_d tCurrent) const override;

  CANT_NODISCARD vel_d getVelocityPlaying() const override;

  CANT_NODISCARD pan_d getPan() const override;

  CANT_NODISCARD bool isSet() const override;

  CANT_NODISCARD bool isPlaying() const override;
  CANT_NODISCARD bool justChangedPlaying() const override;

  CANT_NODISCARD bool justStarted() const;
  CANT_NODISCARD bool justStopped() const;

private:
  /** -- methods -- **/
  CANT_NODISCARD vel_d getVelocity() const override;

  /** -- fields -- **/
  bool m_isPlaying;
  bool m_justChangedPlaying;
  bool m_isSet;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.inl>

#endif // CANTINA_PAN_MIDINOTEINTERNALOUTPUT_HPP