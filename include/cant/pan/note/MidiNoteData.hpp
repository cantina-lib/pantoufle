//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MIDINOTEDATA_HPP
#define CANTINA_MIDINOTEDATA_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN
template <typename Tone_T, typename Vel_T>
class MidiNoteData : MidiNoteDataCompatible {
public:
  /** -- methods -- **/
  MidiNoteData();
  MidiNoteData(id_u8 channel, Tone_T tone, Vel_T velocity);

  template <typename Tone_U, typename Vel_U>
  CANT_EXPLICIT MidiNoteData(const MidiNoteData<Tone_U, Vel_U> &other);

  // Shouldn't be used with  tone_d/vel_d version of note data
  CANT_NODISCARD bool operator==(const MidiNoteData &data) const;
  CANT_NODISCARD bool operator!=(const MidiNoteData &data) const;

  CANT_NODISCARD id_u8 getChannel() const override;
  CANT_NODISCARD tone_d getTone() const override;
  CANT_NODISCARD vel_d getVelocity() const override;

protected:
  /** -- fields -- **/
  id_u8 m_channel;
  Tone_T m_tone;
  Vel_T m_velocity;
};

typedef Array<vel_d, 2> ArrayPan;

class MidiNoteInputData : public MidiNoteData<tone_i8, vel_i8> {
public:
  /** -- methods -- **/
  MidiNoteInputData();
  MidiNoteInputData(id_u8 channel, tone_i8 tone, vel_i8 velocity);

  MidiNoteInputData(const MidiNoteInputData &other);
  MidiNoteInputData &operator=(const MidiNoteInputData &other);

  CANT_NODISCARD tone_i8 getToneNative() const;
  CANT_NODISCARD vel_i8 getVelocityNative() const;

  CANT_NODISCARD bool isPressed() const;
};

class MidiNoteInternalData : public MidiNoteData<tone_d, vel_d> {
public:
  /** -- methods -- **/
  MidiNoteInternalData();
  CANT_EXPLICIT MidiNoteInternalData(const MidiNoteInputData &input);

  void setTone(tone_d tone);
  void setVelocity(vel_d velocity);
  void setPan(pan_d pan);

  CANT_NODISCARD pan_d getPan() const;

private:
  /** -- fields -- **/
  pan_d m_pan;
};

class MidiNoteOutputData : public MidiNoteData<tone_d, vel_d> {
public:
  /** -- methods -- **/
  MidiNoteOutputData();
  CANT_EXPLICIT MidiNoteOutputData(const MidiNoteInternalData &internal);

  CANT_NODISCARD pan_d getPan() const;

private:
  /** -- fields -- **/
  pan_d m_pan;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/note/MidiNoteData.inl>

#endif // CANTINA_MIDINOTEDATA_HPP
