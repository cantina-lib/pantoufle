//
// Created by binabik on 19/09/2020.
//

#include <cant/pan/layer/MidiNoteInputLayer.hpp>
#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiNoteInputLayer::
    MidiNoteInputLayer(size_u numberVoices)
    : m_inputNotes()
    {
        m_inputNotes.reserve(numberVoices);
        for (size_u i = 0; i < numberVoices; ++i)
        {
            m_inputNotes.emplace_back(i);
        }
    }

    const MidiNoteInput&
    MidiNoteInputLayer::
    getVoice(size_u voice) const
    {
        return m_inputNotes.at(voice);
    }

    size_u
    MidiNoteInputLayer::
    getNumberVoices() const
    {
        return m_inputNotes.size();
    }

CANTINA_PAN_NAMESPACE_END

