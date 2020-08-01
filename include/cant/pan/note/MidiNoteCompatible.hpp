//
// Created by binabik on 22/07/2020.
//

#ifndef CANTINA_MIDIPLAYABLE_HPP
#define CANTINA_MIDIPLAYABLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

namespace cant::pan
{
    class MidiNoteDataCompatible
    {
    public:
        virtual ~MidiNoteDataCompatible() = default;
        CANT_NODISCARD virtual byte_m getChannel() const = 0;
        CANT_NODISCARD virtual tone_m getTone() const = 0;


        CANT_NODISCARD virtual bool isPressed() const = 0;
    protected:
        CANT_NODISCARD virtual vel_m getVelocity() const = 0;
    };

    class MidiNoteCompatible
    {
    public:
    public:
        virtual ~MidiNoteCompatible() = default;

        CANT_NODISCARD virtual byte_m getChannel() const = 0;
        CANT_NODISCARD virtual tone_m getTone() const = 0;
        CANT_NODISCARD virtual vel_m getVelocity() const = 0;

        CANT_NODISCARD virtual bool justChanged() const = 0;
    };

    class MidiNoteInputCompatible : public MidiNoteCompatible
    {
    public:
        CANT_NODISCARD virtual bool isPressed() const = 0;

        CANT_NODISCARD virtual time_m getStartingTime() const = 0;

        virtual void update(time_m) = 0;
    };

    class MidiNoteInternalCompatible : public MidiNoteCompatible
    {
    public:
        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_m getLength(time_m tCurrent) const = 0;

        CANT_NODISCARD virtual time_m getStartingTime() const = 0;
    };

    class MidiNoteOutputCompatible : public MidiNoteCompatible
    {
    public:
        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_m getLength(time_m tCurrent) const = 0;

        CANT_NODISCARD virtual vel_m getVelocityPlaying() const = 0;
    };

}

#endif //CANTINA_MIDIPLAYABLE_HPP
