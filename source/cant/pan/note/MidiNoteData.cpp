//
// Created by binabik on 25/07/2020.
//

#include <cant/pan/note/MidiNoteData.hpp>

namespace cant::midi
{

    BaseMidiNoteData::BaseMidiNoteData(byte_m channel)
            : _channel(channel)
    {

    }

    BaseMidiNoteData::BaseMidiNoteData() : _channel() { }

    bool BaseMidiNoteData::operator==(const BaseMidiNoteData &data) const {
        return data._channel == _channel;
    }

    bool BaseMidiNoteData::operator!=(const BaseMidiNoteData &data) const { return !operator==(data); }

    std::ostream &operator<<(std::ostream &out, const BaseMidiNoteData &data) {
        return out << fmt::format("[data] [{0}, {1}, {2}]", (int)data.getChannel(), data.getTone(), data.getVelocity());
    }

    MidiNoteInputData::MidiNoteInputData(tone_mint tone, vel_mint velocity, byte_m channel)
            : BaseMidiNoteData(channel),  _tone(tone), _velocity(velocity)
    {

    }

    MidiNoteInputData::MidiNoteInputData() : BaseMidiNoteData(), _tone(), _velocity() { }

    bool MidiNoteInputData::operator==(const MidiNoteInputData &data) const {
        return BaseMidiNoteData::operator==(data)
               && data._tone == _tone
               && data._velocity== _velocity;
    }

    bool MidiNoteInputData::operator!=(const MidiNoteInputData &data) const { return !operator==(data); }

    MidiNoteOutputData::MidiNoteOutputData(tone_m tone, vel_m velocity, byte_m channel)
            : BaseMidiNoteData(channel),  _tone(tone), _velocity(velocity)
    {

    }

    MidiNoteOutputData::MidiNoteOutputData() : BaseMidiNoteData(), _tone(), _velocity() { }

    MidiNoteInput::MidiNoteInput(tone_m tone, vel_m velocity, byte_m channel, const bool isPressed)
            : _data(tone, velocity, channel), _tStart(), _isPressed(isPressed), _flagChanged(true)
    {
        CANTINA_ASSERT(velocity > static_cast<vel_m>(0))
    }

    MidiNoteInput::MidiNoteInput() : _data(), _tStart(), _isPressed(), _flagChanged() { }

    void MidiNoteInput::update(time_m)
    {
        discardFlagChanged();
    }

    void MidiNoteInput::update(const MidiNoteInputData &data, time_m tCurrent) {
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

    MidiNoteOutput::MidiNoteOutput() : _data(), _isPlaying(false), _justChanged(false) { }

    MidiNoteOutput::
    MidiNoteOutput(
            const tone_m tone,
            const vel_m velocity,
            const byte_m channel,
            const bool isPlaying,
            const bool justChanged)
     : _data(tone, velocity, channel), _isPlaying(isPlaying), _justChanged(justChanged)
    {

    }

    vel_m MidiNoteOutput::getVelocityPlaying() const {
        return isPlaying() ? getVelocity() : static_cast<vel_m>(0);
    }

    std::ostream &operator<<(std::ostream &out, const MidiNoteOutput &output) {
        out << output.getData();
        out << (output.isPlaying() ? " [PLAYING]" : " [NOT_PLAYING]");
        out << " " << (output.justChanged() ? " !CHANGED" : "");
        return out;
    }
}

