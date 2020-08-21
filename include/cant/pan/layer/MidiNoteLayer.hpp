//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTELAYER_HPP
#define CANTINA_TILDE_MIDINOTELAYER_HPP

#pragma once

#include <cant/common/memory.hpp>

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template <class Note_T>
    class MidiNoteLayer
    {
    protected:
        Stream<Note_T> _notes;
    private:
        void initialiseNotes(const size_m numberVoices)
        {
            _notes.reserve(numberVoices);
            for (size_m i = 0; i < numberVoices; ++i)
            {
                _notes.push_back(Note_T(i));
            }
        }
    public:
        CANT_EXPLICIT MidiNoteLayer(size_m numberVoices)
        : _notes()
        {
            initialiseNotes(numberVoices);
        }
        virtual ~MidiNoteLayer() = default;

        CANT_NODISCARD const Note_T& get(size_m voice) const { return _notes.at(voice); }

        CANT_NODISCARD size_m getNumberVoices() const { return _notes.size(); }
    };

    class MidiNoteInputLayer : public MidiNoteLayer<MidiNoteInput>
    {
    public:
        CANT_EXPLICIT MidiNoteInputLayer(size_m numberVoices)
        : MidiNoteLayer<MidiNoteInput>(numberVoices)
        {
        }
        virtual void receive(time_m tCurrent, const MidiNoteInputData &data) = 0;
    };

    template <class Note_T, class PreviousLayerNote_T>
    class MidiNoteInternalOutputLayer : public MidiNoteLayer<Note_T>
    {
    public:
        CANT_EXPLICIT MidiNoteInternalOutputLayer(size_m numberVoices)
        : MidiNoteLayer<Note_T>(numberVoices)
        {

        }

        void receive(const PreviousLayerNote_T& previous)
        {
            PANTOUFLE_TRY_RETHROW({
                this->_notes.at(previous.getVoice()).set(previous);
            })
        }

        void setVoice(const Note_T& note)
        {
            PANTOUFLE_TRY_RETHROW({
                this->_notes.at(note.getVoice()) = note;
            })
        }

        CANT_NODISCARD Note_T& getMutable(size_m voice) { return this->_notes.at(voice); }


        CANT_NODISCARD const Stream<Note_T>& getNotes() const { return this->_notes; }
    };

    using MidiNoteInternalLayer = MidiNoteInternalOutputLayer<MidiNoteInternal, MidiNoteInput>;
    using MidiNoteOutputLayer = MidiNoteInternalOutputLayer<MidiNoteOutput, MidiNoteInternal>;
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDINOTELAYER_HPP
