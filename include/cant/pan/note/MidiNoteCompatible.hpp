//
// Created by binabik on 22/07/2020.
//

#ifndef CANTINA_MIDIPLAYABLE_HPP
#define CANTINA_MIDIPLAYABLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

namespace cant::midi
{
    class MidiNoteCompatible
    {
    public:
        virtual ~MidiNoteCompatible() = default;
        CANT_NODISCARD virtual byte_m getChannel() const = 0;
        CANT_NODISCARD virtual tone_m getTone() const = 0;
        CANT_NODISCARD virtual vel_m getVelocity() const = 0;
    };

    class MidiNoteOutputCompatible : public MidiNoteCompatible
    {
    protected:
        CANT_NODISCARD virtual vel_m getVelocityPlaying() const = 0;
    };
}

#endif //CANTINA_MIDIPLAYABLE_HPP
