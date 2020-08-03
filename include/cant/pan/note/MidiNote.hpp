//
// Created by binabik on 01/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTE_HPP
#define CANTINA_TILDE_MIDINOTE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/pan/common/MidiEvent.hpp>

namespace cant::pan
{

    class MidiNoteInput : MidiNoteInputCompatible
    {
    private:
        MidiNoteInputData _data;
        time_m _tStart;
        bool _isPressed;
        bool _flagChangedPlaying;
        bool _flagChangedTone;
    private:
        void raiseFlagChangedPlaying();
        void raiseFlagChangedNote();
        void discardAllChangeFlags();

        CANT_CONSTEXPR MidiNoteInput(const MidiNoteInput&) = default;

        MidiNoteInput(byte_m channel, tone_m tone, vel_m velocity, bool isPressed);
    public:
        MidiNoteInput();

        void set(time_m tCurrent, const MidiNoteInputData& data);

        void flushChange();

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override    { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD const MidiNoteInputData& getData() const { return _data; }

        CANT_NODISCARD time_m getStartingTime() const override { return _tStart; }

        CANT_NODISCARD bool isPressed() const override   { return _isPressed; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _flagChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _flagChangedTone; }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInput& input);
    };


    class MidiNoteInternal : MidiNoteInternalCompatible
    {
    private:
        MidiNoteInternalData _data;

        time_m _tStart;
        bool _isPlaying;
        bool _justChangedPlaying;
        bool _justChangedTone;

    public:
        MidiNoteInternal();

        void set(const MidiNoteInput& input);

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        void setPlaying(bool isPlaying) { _isPlaying = isPlaying; }
        void setChangedPlaying(const bool justChanged) { _justChangedPlaying = justChanged; }
        void setChangedTone(const bool justChanged) { _justChangedTone = justChanged; }

        void setTone(const tone_m tone) { _data.setTone(tone); }
        void setVelocity(const vel_m velocity) { _data.setVelocity(velocity); }

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD time_m getStartingTime() const override { return _tStart; }

        CANT_NODISCARD const MidiNoteInternalData& getData() const { return _data; }

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _justChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _justChangedTone; }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInternal& output);
    };

    class MidiNoteOutput : MidiNoteOutputCompatible
    {
    private:
        MidiNoteOutputData _data;

        time_m _tStart;
        bool _isPlaying;
        bool _justChangedPlaying;
        bool _justChangedTone;
    private:
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

    public:
        MidiNoteOutput();

        void set(const MidiNoteInternal& internal);

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocityPlaying() const override;

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _justChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _justChangedTone; }

        CANT_NODISCARD bool justStarted() const { return _justChangedPlaying && isPlaying(); }
        CANT_NODISCARD bool justStopped() const { return _justChangedPlaying && !isPlaying(); }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInternal& output);

    };
}

#endif //CANTINA_TILDE_MIDINOTE_HPP
