//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTE_INL
#define CANTINA_TILDE_MIDINOTE_INL

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

template <class Data_T>
MidiNote<Data_T>::MidiNote(size_u voice)
    : m_data(), m_voice(voice), m_tStart() {}

template <typename Data_T>
MidiNote<Data_T>::MidiNote(const MidiNote<Data_T> &other)
    : m_data(other.m_data), m_voice(other.m_voice), m_tStart(other.m_tStart) {}

template <typename Data_T>
MidiNote<Data_T> &MidiNote<Data_T>::operator=(const MidiNote &other) {
  m_data = other.m_data;
  m_voice = other.m_voice;
  m_tStart = other.m_tStart;
  return *this;
}

template <class Data_T>
CANT_INLINE const Data_T &MidiNote<Data_T>::getData() const {
  return m_data;
}

template <class Data_T> CANT_INLINE size_u MidiNote<Data_T>::getVoice() const {
  return m_voice;
}

template <class Data_T> CANT_INLINE id_u8 MidiNote<Data_T>::getChannel() const {
  return m_data.getChannel();
}

template <class Data_T> CANT_INLINE tone_d MidiNote<Data_T>::getTone() const {
  return m_data.getTone();
}

template <class Data_T>
CANT_INLINE vel_d MidiNote<Data_T>::getVelocity() const {
  return m_data.getVelocity();
}

template <class Data_T>
CANT_INLINE time_d MidiNote<Data_T>::getStartingTime() const {
  return m_tStart;
}

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_TILDE_MIDINOTE_INL
