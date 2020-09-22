//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/note/MidiNoteInternalOutput.hpp>
#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiNoteInternal::
    MidiNoteInternal(const size_u voice)
    : MidiNote<MidiNoteInternalData>(voice),
      m_isPlaying(false),
      m_justChangedPlaying(false)
    {

    }

    void
    MidiNoteInternal::
    set(const MidiNoteInput& input)
    {
        m_data = MidiNoteInternalData(input.getData());
        m_tStart = input.getStartingTime();
        m_isPlaying = input.isPlaying(); // at input stage, playing if and only if pressed
        m_justChangedPlaying = input.justChangedPlaying();
    }


    MidiNoteOutput::
    MidiNoteOutput(const size_u voice)
    : MidiNote<MidiNoteOutputData>(voice),
      m_isPlaying(false),
      m_justChangedPlaying(false),
      m_isSet(false)
    {

    }

    void
    MidiNoteOutput::
    set(const MidiNoteInternal &internal)
    {
        m_data = MidiNoteOutputData(internal.getData());
        m_tStart = internal.getStartingTime();
        m_isPlaying = internal.isPlaying();
        m_justChangedPlaying = internal.justChangedPlaying();
        m_isSet = true;
    }

CANTINA_PAN_NAMESPACE_END
