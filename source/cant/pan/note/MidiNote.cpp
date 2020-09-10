//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    MidiNoteInput::MidiNoteInput(const size_u voice)
    : MidiNote<MidiNoteInputData>(voice),
      m_isPressed(false),
      m_flagChangedPressed(false),
      m_flagChangedTone(false)
    {

    }

    void
    MidiNoteInput::
    flushChange()
    {
        discardAllChangeFlags();
    }

    void
    MidiNoteInput::
    set(const time_d tCurrent, const MidiNoteInputData &data)
    {
        const bool wasPlaying = isPlaying();
        const tone_u8 lastTone = getTone();

        m_isPressed = data.isPressed();

        if (data.isPressed())
        {
            if (!wasPlaying)
            {
                // a note is born!
                m_tStart = tCurrent;
            }
            m_data = data;
        }
        m_flagChangedPressed = isPlaying() != wasPlaying;
        m_flagChangedTone = getTone() != lastTone;
    }

    void MidiNoteInput::discardAllChangeFlags()
    {
        m_flagChangedPressed = false;
        m_flagChangedTone = false;
    }



    MidiNoteInternal::
    MidiNoteInternal(const size_u voice)
    : MidiNote<MidiNoteInternalData>(voice),
      m_isPlaying(false),
      m_justChangedPlaying(false),
      m_justChangedTone(false)
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
        m_justChangedTone = input.justChangedTone();
    }


    MidiNoteOutput::
    MidiNoteOutput(const size_u voice)
    : MidiNote<MidiNoteOutputData>(voice),
      m_isPlaying(false),
      m_justChangedPlaying(false),
      m_justChangedTone(false)
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
        m_justChangedTone = internal.justChangedTone();
    }


}
