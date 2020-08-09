//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDIPROCESSOR_HPP
#define CANTINA_MIDIPROCESSOR_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/pan/note/MidiNote.hpp>

#include <cant/pan/layer/MidiNoteLayer.hpp>

namespace cant::pan
{
    class MidiProcessor
    {
    public:
        virtual void update(time_m tCurrent) = 0;

        virtual void process(MidiNoteInternal& in) = 0;
    };

    class MidiProcessorMemory : public MidiProcessor
    {
    protected:
        MidiNoteInternalLayer _memory;
    public:
        virtual ~MidiProcessorMemory() = default;
        CANT_EXPLICIT MidiProcessorMemory(const size_m numberVoices)
        : _memory(numberVoices)
        {

        }

        CANT_NODISCARD CANT_INLINE
        size_m getNumberVoices() const { return _memory.getNumberVoices(); }

        void update(time_m tCurrent) override = 0;

        void process(MidiNoteInternal& in) override = 0;
    };
}

#endif //CANTINA_MIDIPROCESSOR_HPP
