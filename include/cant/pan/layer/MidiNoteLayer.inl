//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTELAYER_INL
#define CANTINA_TILDE_MIDINOTELAYER_INL

#pragma once

#include <cant/pan/note/note_forward.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template<class Note_T>
    void
    MidiNoteLayer<Note_T>::
    initialiseNotes(const size_m numberVoices)
    {
        m_notes.reserve(numberVoices);
        for (size_m i = 0; i < numberVoices; ++i)
        {
            m_notes.push_back(Note_T { i });
        }
    }

    template<class Note_T>
    MidiNoteLayer<Note_T>::
    MidiNoteLayer(size_m numberVoices)
        : m_notes()

    {
        initialiseNotes(numberVoices);
    }

    template<class Note_T>
    CANT_NODISCARD CANT_INLINE
    const Note_T &
    MidiNoteLayer<Note_T>::
    getVoice(size_m voice) const
    {
        return m_notes.at(voice);
    }

    template<class Note_T>
    CANT_NODISCARD CANT_INLINE
    size_m
    MidiNoteLayer<Note_T>::
    getNumberVoices() const
    {
        return m_notes.size();
    }



    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    MidiNoteInternalOutputLayer(size_m numberVoices)
            : MidiNoteLayer<Note_T>(numberVoices)
    {

    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE
    void
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    receive(const PreviousLayerNote_T &previous)
    {
          this->m_notes.at(previous.getVoice()).set(previous);
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE
    void
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    setVoice(const Note_T &note)
    {
          this->m_notes.at(note.getVoice()) = note;
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_NODISCARD CANT_INLINE
    Note_T &
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::getVoiceMutable(size_m voice)
    {
        return this->m_notes.at(voice);
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_NODISCARD CANT_INLINE
    const Stream <Note_T> &
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::getNotes() const
    {
        return this->m_notes;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTELAYER_INL
