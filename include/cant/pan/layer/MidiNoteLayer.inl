//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTELAYER_INL
#define CANTINA_TILDE_MIDINOTELAYER_INL

#pragma once

#include <cant/common/CantinaException.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template<class Note_T>
    void
    MidiNoteLayer<Note_T>::
    initialiseNotes(const size_m numberVoices)
    {
        _notes.reserve(numberVoices);
        for (size_m i = 0; i < numberVoices; ++i)
        {
            _notes.push_back(Note_T(i));
        }
    }

    template<class Note_T>
    MidiNoteLayer<Note_T>::MidiNoteLayer(size_m numberVoices)
            : _notes()
    {
        initialiseNotes(numberVoices);
    }

    template<class Note_T>
    CANT_NODISCARD CANT_INLINE const Note_T &
    MidiNoteLayer<Note_T>::
    getVoice(size_m voice) const
    {
        return _notes.at(voice);
    }

    template<class Note_T>
    CANT_NODISCARD CANT_INLINE size_m
    MidiNoteLayer<Note_T>::
    getNumberVoices() const
    {
        return _notes.size();
    }


    CANT_INLINE MidiNoteInputLayer::
    MidiNoteInputLayer(size_m numberVoices)
            : MidiNoteLayer<MidiNoteInput>(numberVoices)
    {
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    MidiNoteInternalOutputLayer(size_m numberVoices)
            : MidiNoteLayer<Note_T>(numberVoices)
    {

    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE void
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    receive(const PreviousLayerNote_T &previous)
    {
        PANTOUFLE_TRY_RETHROW({
                                      this->_notes.at(previous.getVoice()).set(previous);
                              })
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_INLINE void
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::
    setVoice(const Note_T &note)
    {
        PANTOUFLE_TRY_RETHROW({
                                      this->_notes.at(note.getVoice()) = note;
                              })
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_NODISCARD CANT_INLINE Note_T &
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::getVoiceMutable(size_m voice)
    {
        return this->_notes.at(voice);
    }

    template<class Note_T, class PreviousLayerNote_T>
    CANT_NODISCARD CANT_INLINE const Stream <Note_T> &
    MidiNoteInternalOutputLayer<Note_T, PreviousLayerNote_T>::getNotes() const
    {
        return this->_notes;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTELAYER_INL
