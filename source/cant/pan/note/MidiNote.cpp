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
            if (!_data.isPressed())
            {
                // a note is born!
                _tStart = tCurrent;
               raiseFlagChangedPlaying();
            }
            if (isToneDifferent)
            {
                raiseFlagChangedNote();
            }
            _data = data;
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
    _isPlaying(false),
    _justChangedPlaying(false),
    _justChangedTone(false)
    {

    }

    void
    MidiNoteInternal::
    set(const MidiNoteInput& input)
    {
        _data = MidiNoteInternalData(input.getData());
        _tStart = input.getStartingTime();
        _isPlaying = input.isPressed(); // at input stage, playing if and only if pressed
        _justChangedPlaying = input.justChangedPlaying();
        _justChangedTone = input.justChangedTone();
    }

    MidiNoteOutput::
    MidiNoteOutput(const size_m voice)
    : MidiNote<MidiNoteOutputData>(voice),
    _isPlaying(false),
    _justChangedPlaying(false),
    _justChangedTone(false)
    {

    }

    void
    MidiNoteOutput::
    set(const MidiNoteInternal &internal)
    {
        _data = MidiNoteOutputData(internal.getData());
        _tStart = internal.getStartingTime();
        _isPlaying = internal.isPlaying();
        _justChangedPlaying = internal.justChangedPlaying();
    }

    vel_m
    MidiNoteOutput::
    getVelocityPlaying() const
    {
        return isPlaying() ? getVelocity() : static_cast<vel_m>(0);
    }

}
