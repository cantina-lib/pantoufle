//
// Created by binabik on 01/08/2020.
//

#include <cant/pan/note/MidiNote.hpp>

namespace cant::pan
{

    MidiNoteInput::
    MidiNoteInput(byte_m channel, tone_m tone, vel_m velocity, const bool isPressed)
            : _data(channel, tone, velocity), _tStart(), _isPressed(isPressed), _flagChangedPlaying(true)
    {
        CANTINA_ASSERT(velocity > static_cast<vel_m>(0))
    }

    MidiNoteInput::MidiNoteInput()
    : _data(),
      _tStart(),
      _isPressed(false),
      _flagChangedPlaying(false)
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
    set(time_m tCurrent, const MidiNoteInputData &data)
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

    std::ostream &operator<<(std::ostream &out, const MidiNoteInput &input)
    {
        out << "[input] [{ " << input.getData() << " }";
        out << (input.isPressed() ? " [PRESSED]" : " [RELEASED]" );
        out << (input.justChangedPlaying() ? " !CHANGE" : "");
        out << "]";
        return out;
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

    MidiNoteInternalData::
    MidiNoteInternalData()
            : MidiNoteData()
    {

    }

    MidiNoteInternalData::
    MidiNoteInternalData(const MidiNoteInputData &input)
            : MidiNoteData<vel_m, tone_m>(input)
    {

    }

    MidiNoteInternal::
    MidiNoteInternal()
            : _data(),
              _tStart(),
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
    MidiNoteOutput()
    : _data(),
      _tStart(),
      _isPlaying(false),
      _justChangedPlaying(false)
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

    std::ostream &operator<<(std::ostream &out, const MidiNoteInternal &output)
    {
        out << output.getData();
        out << (output.isPlaying() ? " [PLAYING]" : " [NOT_PLAYING]");
        out << " " << (output.justChangedPlaying() ? " !CHANGED" : "");
        return out;
    }
}
