//
// Created by binabik on 22/07/2020.
//

#ifndef CANTINA_MIDIPLAYABLE_HPP
#define CANTINA_MIDIPLAYABLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/memory.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiNoteDataCompatible
    {
    public:
        // no virtual destructor for interfaces!
        CANT_NODISCARD virtual byte_m getChannel() const = 0;
        CANT_NODISCARD virtual tone_m getTone() const = 0;


        CANT_NODISCARD virtual bool isPressed() const = 0;
    protected:
        CANT_NODISCARD virtual vel_m getVelocity() const = 0;
    };

    class MidiNoteCompatible
    {
    public:
        CANT_NODISCARD virtual byte_m getChannel() const = 0;
        CANT_NODISCARD virtual tone_m getTone() const = 0;
        CANT_NODISCARD virtual vel_m getVelocity() const = 0;

        CANT_NODISCARD virtual time_m getStartingTime() const = 0;

        CANT_NODISCARD virtual bool justChangedPlaying() const = 0;
        CANT_NODISCARD virtual bool justChangedTone() const = 0;
    };

    class MidiNoteInputCompatible
    {
    public:
        CANT_NODISCARD virtual bool isPressed() const = 0;

    };

    class MidiNoteInternalCompatible
    {
    public:
        CANT_NODISCARD virtual pan_m getPan() const = 0;

         virtual void setTone(tone_m tone) = 0;
         virtual void setVelocity(vel_m velocity) = 0;
         virtual void setPan(pan_m pan) = 0;

        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_m getLength(time_m tCurrent) const = 0;
    };

    class MidiNoteOutputCompatible
    {
    public:
        CANT_NODISCARD virtual vel_m getPan() const = 0;

        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_m getLength(time_m tCurrent) const = 0;

        CANT_NODISCARD virtual vel_m getVelocityPlaying() const = 0;
        CANT_NODISCARD virtual Array<vel_m, 2> getVelocityPanned() const = 0;
    };

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDIPLAYABLE_HPP
