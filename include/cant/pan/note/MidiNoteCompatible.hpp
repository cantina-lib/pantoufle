//
// Created by binabik on 22/07/2020.
//

#ifndef CANTINA_MIDIPLAYABLE_HPP
#define CANTINA_MIDIPLAYABLE_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiNoteDataCompatible
    {
    public:
        /** -- methods -- **/
        // virtual destructor even for interfaces!
        // https://stackoverflow.com/questions/3628529/should-c-interfaces-have-a-virtual-destructor
        virtual ~MidiNoteDataCompatible() = default;

        CANT_NODISCARD virtual id_u8 getChannel() const = 0;
        CANT_NODISCARD virtual tone_d getTone() const = 0;

    protected:
        /** -- methods -- **/
        CANT_NODISCARD virtual vel_d getVelocity() const = 0;
    };

    class MidiNoteCompatible
    {
    public:
        /** -- methods -- **/
        virtual ~MidiNoteCompatible() = default;

        CANT_NODISCARD virtual id_u8 getChannel() const = 0;
        CANT_NODISCARD virtual tone_d getTone() const = 0;
        CANT_NODISCARD virtual vel_d getVelocity() const = 0;

        CANT_NODISCARD virtual time_d getStartingTime() const = 0;

        CANT_NODISCARD virtual bool justChangedPlaying() const = 0;
        CANT_NODISCARD virtual bool justChangedTone() const = 0;
    };

    class MidiNoteInputCompatible
    {
    public:
        /** -- methods -- **/
        virtual ~MidiNoteInputCompatible() = default;

        CANT_NODISCARD virtual bool isPlaying() const = 0;
    };

    class MidiNoteInternalCompatible
    {
    public:
        /** -- methods -- **/
        virtual ~MidiNoteInternalCompatible() = default;

        CANT_NODISCARD virtual pan_d getPan() const = 0;

         virtual void setTone(tone_d tone) = 0;
         virtual void setVelocity(vel_d velocity) = 0;
         virtual void setPan(pan_d pan) = 0;

        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_d getLength(time_d tCurrent) const = 0;
    };

    class MidiNoteOutputCompatible
    {
    public:
        /** -- methods -- **/
        virtual ~MidiNoteOutputCompatible() = default;


        CANT_NODISCARD virtual vel_d getPan() const = 0;

        CANT_NODISCARD virtual bool isSet() const = 0;

        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual time_d getLength(time_d tCurrent) const = 0;

        CANT_NODISCARD virtual vel_d getVelocityPlaying() const = 0;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDIPLAYABLE_HPP
