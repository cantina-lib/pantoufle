//
// Created by binabik on 18/07/2020.
//

#ifndef CANTINA_MIDINOTEDATA_HPP
#define CANTINA_MIDINOTEDATA_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/common/MidiTimer.hpp>

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
}

#endif //CANTINA_MIDINOTEDATA_HPP
