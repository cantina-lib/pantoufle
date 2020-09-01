//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTELAYER_HPP
#define CANTINA_TILDE_MIDINOTELAYER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/note/note_forward.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    template <class Note_T>
    class MidiNoteLayer
    {
    public:
        /** -- methods  -- **/
        CANT_EXPLICIT MidiNoteLayer(size_m numberVoices);
        virtual ~MidiNoteLayer() = default;

        CANT_NODISCARD const Note_T& getVoice(size_m voice) const;
        CANT_NODISCARD size_m getNumberVoices() const;
    protected:
        /** -- fields -- **/
        Stream<Note_T> m_notes;
    private:
        /** -- methods  -- **/
        void initialiseNotes(size_m numberVoices);
    };



    class MidiNoteInputLayer : public MidiNoteLayer<MidiNoteInput>
    {
    public:
        /** -- methods  -- **/
        CANT_EXPLICIT MidiNoteInputLayer(size_m numberVoices);
        virtual void receive(time_m tCurrent, const MidiNoteInputData &data) = 0;
    };


    template <class Note_T, class PreviousLayerNote_T>
    class MidiNoteInternalOutputLayer : public MidiNoteLayer<Note_T>
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteInternalOutputLayer(size_m numberVoices);

        void receive(const PreviousLayerNote_T& previous);
        void setVoice(const Note_T& note);

        CANT_NODISCARD Note_T& getVoiceMutable(size_m voice);
        CANT_NODISCARD const Stream<Note_T>& getNotes() const;
    };


    using MidiNoteInternalLayer = MidiNoteInternalOutputLayer<MidiNoteInternal, MidiNoteInput>;
    using MidiNoteOutputLayer = MidiNoteInternalOutputLayer<MidiNoteOutput, MidiNoteInternal>;
}

#include <cant/common/undef_macro.hpp>

#include "MidiNoteLayer.inl"

#endif //CANTINA_TILDE_MIDINOTELAYER_HPP
