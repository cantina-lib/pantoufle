//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MIDINOTEDATA_HPP
#define CANTINA_MIDINOTEDATA_HPP

#pragma once

#include <iostream>

#include <fmt/format.h>

#include <cant/pan/Time.hpp>

#include <cant/pan/types.hpp>
#include <cant/pan/note/MidiNoteCompatible.hpp>

namespace cant::midi {

    class BaseMidiNoteData : MidiNoteCompatible
    {
    private:
        byte_m _channel;
    public:
        CANT_EXPLICIT BaseMidiNoteData(byte_m channel);

        BaseMidiNoteData();
        CANT_CONSTEXPR BaseMidiNoteData(const BaseMidiNoteData &) = default;

        CANT_NODISCARD bool operator==(const BaseMidiNoteData& data) const;
        CANT_NODISCARD bool operator!=(const BaseMidiNoteData& data) const;

        CANT_NODISCARD byte_m getChannel() const override { return _channel; }
        CANT_NODISCARD tone_m getTone() const override = 0;
        CANT_NODISCARD vel_m getVelocity() const override = 0;

        friend std::ostream& operator<<(std::ostream& out, const BaseMidiNoteData& data);
    };

    class MidiNoteInputData final : public BaseMidiNoteData
    {
    private:
        tone_mint _tone;
        vel_mint _velocity;
    public:
        MidiNoteInputData(tone_mint tone, vel_mint velocity, byte_m channel);

        MidiNoteInputData();
        CANT_CONSTEXPR MidiNoteInputData(const MidiNoteInputData &) = default;

        CANT_NODISCARD bool operator==(const MidiNoteInputData& data) const;

        CANT_NODISCARD bool operator!=(const MidiNoteInputData& data) const;

        CANT_NODISCARD tone_m getTone() const override { return static_cast<tone_m>(_tone); }
        CANT_NODISCARD vel_m getVelocity() const override{ return static_cast<tone_m>(_velocity); }

        CANT_NODISCARD bool isPressed() const { return static_cast<bool>(_velocity); }
    };

    class MidiNoteOutputData final : public BaseMidiNoteData
    {
    private:
        tone_m _tone;
        vel_m _velocity;
    public:
        MidiNoteOutputData(tone_m tone, vel_m velocity, byte_m channel);

        MidiNoteOutputData();
        CANT_CONSTEXPR MidiNoteOutputData(const MidiNoteOutputData&) = default;

        CANT_NODISCARD bool operator==(const MidiNoteOutputData& data) const = delete;
        CANT_NODISCARD bool operator!=(const MidiNoteOutputData& data) const = delete;

        CANT_NODISCARD tone_m getTone() const override { return _tone; }
        CANT_NODISCARD vel_m getVelocity() const override{ return _velocity; }

    };

    class RawMidiNote;

    class MidiNoteInput : MidiNoteCompatible
    {
        friend RawMidiNote;
    private:
        MidiNoteInputData _data;
        time_m _tStart;
        bool _isPressed;
        bool _flagChanged;
    private:
        void raiseFlagChanged();
        void discardFlagChanged();
    protected:

        MidiNoteInput(tone_m tone, vel_m velocity, byte_m channel, bool isPressed);
        CANT_CONSTEXPR MidiNoteInput(const MidiNoteInput&) = default;


        CANT_NODISCARD MidiNoteInputData getData() const { return _data; }

    public:
        MidiNoteInput();

        // does not need a time, just as long as it is called at every iteration
        void update(time_m);

        void update(const MidiNoteInputData& data, time_m tCurrent);


        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD bool isPressed() const { return _isPressed; }
        CANT_NODISCARD bool justChanged() const { return _flagChanged; }

        CANT_NODISCARD time_m getStartingTime() const { return _tStart; }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInput& input);

    };


    class MidiNoteOutput : MidiNoteOutputCompatible
    {
    private:
        MidiNoteOutputData _data;
        bool _isPlaying;
        bool _justChanged;
    private:

        CANT_NODISCARD MidiNoteOutputData getData() const { return _data; }

        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }
    public:
        MidiNoteOutput();

        MidiNoteOutput(
                tone_m tone,
                vel_m velocity,
                byte_m channel,
                bool isPlaying,
                bool justChanged
        );

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocityPlaying() const override;

        CANT_NODISCARD bool isPlaying() const { return _isPlaying; }
        CANT_NODISCARD bool justChanged() const { return _justChanged; }

        CANT_NODISCARD bool justStarted() const { return _justChanged && isPlaying(); }
        CANT_NODISCARD bool justStopped() const { return _justChanged && !isPlaying(); }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteOutput& output);
    };



}

#endif //CANTINA_MIDINOTEDATA_HPP
