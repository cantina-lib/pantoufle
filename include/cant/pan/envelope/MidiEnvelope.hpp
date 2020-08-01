//
// Created by piptouque on 28/04/2020.
//

#ifndef PANTOUFLEENVELOPE_HPP
#define PANTOUFLEENVELOPE_HPP

#pragma once


#include <cant/common/formatting.hpp>
#include <cant/pan/common/types.hpp>
#include <cant/pan/common/Time.hpp>

#include <cant/pan/note/MidiNoteData.hpp>

namespace cant::pan
{

    /**
     * Envelopes should not have internal states
     * but compute everything from input note (contains starting time)
     * and current time.
     **/
    template <typename T>
    class MidiEnvelope
    {
    public:
        MidiEnvelope() = default;
        virtual ~MidiEnvelope() = default;

        // envelopes are state-less, so const here
        virtual void apply(time_m tCurrent, MidiNoteInternal& note) const = 0;
    };

    class ToneEnvelope : public MidiEnvelope<tone_m>
    {
    public:
        void apply(time_m tCurrent, MidiNoteInternal& note) const override = 0;
    };


    class VelocityEnvelope : public MidiEnvelope<vel_m>
    {
    public:
        void apply(time_m tCurrent, MidiNoteInternal& note) const override = 0;
    };
}

#endif //PANTOUFLEENVELOPE_HPP
