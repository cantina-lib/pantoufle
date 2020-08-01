//
// Created by binabik on 25/07/2020.
//

#include <cant/pan/note/MidiNoteData.hpp>

namespace cant::pan
{

    MidiNoteInput::
    MidiNoteInput(byte_m channel, tone_m tone, vel_m velocity, const bool isPressed)
     : _data(channel, tone, velocity), _tStart(), _isPressed(isPressed), _flagChanged(true)
    {
        CANTINA_ASSERT(velocity > static_cast<vel_m>(0))
    }

    MidiNoteInput::MidiNoteInput()
    : _data(),
    _tStart(),
    _isPressed(),
    _flagChanged()
    {

    }

    void
    MidiNoteInput::
    update(time_m)
    {
        discardFlagChanged();
    }

    void
    MidiNoteInput::
    update(const MidiNoteInputData &data, time_m tCurrent)
    {
        const bool isInputPressed = data.isPressed();

        if (isInputPressed)
        {
            if (_data != data)
            {
                CANTINA_TRY_RETHROW({
                    _tStart = Time::checkTime(tCurrent);
                })
                raiseFlagChanged();
            }
            _data = data;
        }
        else
        {
            raiseFlagChanged();
        }

        _isPressed = isInputPressed;
    }

    std::ostream &operator<<(std::ostream &out, const MidiNoteInput &input)
    {
        out << "[input] [{ " << input.getData() << " }";
        out << (input.isPressed() ? " [PRESSED]" : " [RELEASED]" );
        out << (input.justChanged() ? " !CHANGE" : "");
        out << "]";
        return out;
    }

    void MidiNoteInput::raiseFlagChanged()
    {
        _flagChanged = true;
    }

    void MidiNoteInput::discardFlagChanged()
    {
        _flagChanged = false;
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
    _justChanged(false)
    {

    }

    void
    MidiNoteInternal::
    update(const MidiNoteInput& input)
    {
        _data = MidiNoteInternalData(input.getData());
        _tStart = input.getStartingTime();
        _isPlaying = input.isPressed(); // at input stage, playing if and only if pressed
        _justChanged = input.justChanged();

    }

    MidiNoteOutput::
    MidiNoteOutput()
    : _data(),
    _tStart(),
      _isPlaying(),
    _justChanged()
    {

    }

    void
    MidiNoteOutput::
    update(const MidiNoteInternal &internal)
    {
        _data = MidiNoteOutputData(internal.getData());
        _tStart = internal.getStartingTime();
        _isPlaying = internal.isPlaying();
        _justChanged = internal.justChanged();
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
        out << " " << (output.justChanged() ? " !CHANGED" : "");
        return out;
    }
}
