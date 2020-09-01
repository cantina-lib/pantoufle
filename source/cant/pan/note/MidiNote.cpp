//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    MidiNoteInput::
    MidiNoteInput(size_m voice, byte_m channel, tone_m tone, vel_m velocity, bool isPressed)
    : MidiNote(voice, channel, tone, velocity),
    _isPressed(isPressed),
    _flagChangedPlaying(true),
    _flagChangedTone(false)
    {
        CANTINA_ASSERT(
                velocity > static_cast<vel_m>(0),
               "Velocity should not be null. Use changedPlaying if note is note is not playing.");
    }

    MidiNoteInput::MidiNoteInput(const size_m voice)
    : MidiNote<MidiNoteInputData>(voice),
      _isPressed(false),
      _flagChangedPlaying(false),
      _flagChangedTone(false)
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
    set(const time_m tCurrent, const MidiNoteInputData &data)
    {
        const bool isInputPressed = data.isPressed();
        const bool isToneDifferent = data.getTone() != getTone();

        if (isInputPressed)
        {
            if (!m_data.isPressed())
            {
                // a note is born!
                m_tStart = tCurrent;
               raiseFlagChangedPlaying();
            }
            if (isToneDifferent)
            {
                raiseFlagChangedNote();
            }
            m_data = data;
        }
        else
        {
            raiseFlagChangedPlaying();
        }
        _isPressed = isInputPressed;
    }

    void MidiNoteInput::raiseFlagChangedPlaying()
    {
        _flagChangedPlaying = true;
    }

    void MidiNoteInput::raiseFlagChangedNote()
    {
        _flagChangedTone = true;
    }

    void MidiNoteInput::discardAllChangeFlags()
    {
        _flagChangedPlaying = false;
        _flagChangedTone = false;
    }



    MidiNoteInternal::
    MidiNoteInternal(const size_m voice)
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
        m_isPlaying = input.isPressed(); // at input stage, playing if and only if pressed
        m_justChangedPlaying = input.justChangedPlaying();
        m_justChangedTone = input.justChangedTone();
    }


    MidiNoteOutput::
    MidiNoteOutput(const size_m voice)
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
    }


}
