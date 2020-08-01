//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MIDINOTEDATA_HPP
#define CANTINA_MIDINOTEDATA_HPP

#pragma once

#include <iostream>

#include <fmt/format.h>

#include <cant/pan/common/Time.hpp>

#include <cant/pan/common/types.hpp>
#include <cant/pan/note/MidiNoteCompatible.hpp>

namespace cant::pan
{

    template <typename Tone_T, typename Vel_T>
    class MidiNoteData : MidiNoteDataCompatible
    {
    protected:
        byte_m _channel;
        Tone_T _tone;
        Vel_T _velocity;
    public:
        MidiNoteData(byte_m channel, Tone_T tone, Vel_T velocity)
        : _channel(channel), _tone(tone), _velocity(velocity)
        {

        }

        template <typename Tone_U, typename Vel_U>
        CANT_EXPLICIT MidiNoteData(const MidiNoteData<Tone_U, Vel_U>& other)
        : _channel(other.getChannel()),
        _tone(static_cast<Tone_T>(other.getTone())),
        _velocity(static_cast<Vel_T>(other.getVelocity()))
        {

        }

        CANT_CONSTEXPR MidiNoteData()
        : _channel(), _tone(), _velocity()
        {

        }

        MidiNoteData(const MidiNoteData &) = default;

        // Shouldn't be used with tone_m/vel_m
        CANT_NODISCARD bool operator==(const MidiNoteData& data) const
        {
            return data._channel == _channel
                   && data._tone == _tone
                   && data._velocity== _velocity;
        }
        CANT_NODISCARD bool operator!=(const MidiNoteData& data) const
        {
            return !operator==(data);
        }

        CANT_NODISCARD byte_m getChannel() const override { return _channel; }
        CANT_NODISCARD tone_m getTone() const override { return static_cast<tone_m>(_tone); };
        CANT_NODISCARD vel_m getVelocity() const override { return static_cast<vel_m>(_velocity); }

        CANT_NODISCARD bool isPressed() const override { return static_cast<bool>(_velocity); }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteData& data)
        {
            out << "[data] ";
            out << fmt::format("[{0}, {1}, {2}]", data.getChannel(), data.getTone(), data.getVelocity());
            return out;
        }
    };


    using MidiNoteInputData = MidiNoteData<tone_mint, vel_mint>;
    using MidiNoteOutputData = MidiNoteData<tone_m, vel_m>;

    class MidiNoteInternalData : public MidiNoteData<tone_m, vel_m>
    {
    public:
        MidiNoteInternalData();
        CANT_EXPLICIT MidiNoteInternalData(const MidiNoteInputData& input);

        void setTone(const tone_m tone) { _tone = tone; }
        void setVelocity(const vel_m velocity) { _velocity = velocity; }

    };



    class MidiNoteInput : MidiNoteInputCompatible
    {
    private:
        MidiNoteInputData _data;
        time_m _tStart;
        bool _isPressed;
        bool _flagChanged;
    private:
        void raiseFlagChanged();
        void discardFlagChanged();

        CANT_CONSTEXPR MidiNoteInput(const MidiNoteInput&) = default;

        MidiNoteInput(byte_m channel, tone_m tone, vel_m velocity, bool isPressed);
    public:
        MidiNoteInput();

        // does not need a time, just as long as it is called at every iteration
        void update(const MidiNoteInputData& data, time_m tCurrent);

        void update(time_m tCurrent) override;

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override    { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD const MidiNoteInputData& getData() const { return _data; }

        CANT_NODISCARD time_m getStartingTime() const override { return _tStart; }

        CANT_NODISCARD bool isPressed() const override   { return _isPressed; }
        CANT_NODISCARD bool justChanged() const override { return _flagChanged; }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInput& input);
    };


    class MidiNoteInternal : MidiNoteInternalCompatible
    {
    private:
        MidiNoteInternalData _data;

        time_m _tStart;
        bool _isPlaying;
        bool _justChanged;

    public:
        MidiNoteInternal();

        void update(const MidiNoteInput& input);

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        void setPlaying(const bool isPlaying)   { _isPlaying = isPlaying; }
        void setChanged(const bool justChanged) { _justChanged = justChanged; }

        void setTone(const tone_m tone) { _data.setTone(tone); }
        void setVelocity(const vel_m velocity) { _data.setVelocity(velocity); }

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD time_m getStartingTime() const override { return _tStart; }

        CANT_NODISCARD const MidiNoteInternalData& getData() const { return _data; }

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChanged() const override { return _justChanged; }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInternal& output);
    };

    class MidiNoteOutput : MidiNoteOutputCompatible
    {
    private:
        MidiNoteOutputData _data;

        time_m _tStart;
        bool _isPlaying;
        bool _justChanged;
    private:
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

    public:
        MidiNoteOutput();

        void update(const MidiNoteInternal& internal);

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocityPlaying() const override;

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChanged() const override { return _justChanged; }

        CANT_NODISCARD bool justStarted() const { return _justChanged && isPlaying(); }
        CANT_NODISCARD bool justStopped() const { return _justChanged && !isPlaying(); }

        friend std::ostream& operator<<(std::ostream& out, const MidiNoteInternal& output);

    };


}

#endif //CANTINA_MIDINOTEDATA_HPP
