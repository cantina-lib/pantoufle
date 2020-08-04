//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDIPROCESSOR_HPP
#define CANTINA_MIDIPROCESSOR_HPP

#pragma once

#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

namespace cant::pan
{
    class MidiProcessor
    {

    public:
        virtual ~MidiProcessor() = default;

        CANT_NODISCARD CANT_INLINE virtual size_m getNumberVoices() const = 0;

        virtual void update(time_m tCurrent) = 0;

        virtual void processVoice(size_m iVoice, MidiNoteInternal& in) = 0;
    };

    class MidiProcessorMemory : public MidiProcessor
    {
    protected:
        Stream<MidiNoteInternal> _memory;
    public:
        CANT_EXPLICIT MidiProcessorMemory(const size_m numberVoices)
        : _memory(numberVoices)
        {

        }

        CANT_NODISCARD CANT_INLINE
        size_m getNumberVoices() const final { return _memory.size(); }

        void update(time_m tCurrent) override = 0;

        void processVoice(size_m iVoice, MidiNoteInternal& in) override = 0;
    };
}

#endif //CANTINA_MIDIPROCESSOR_HPP
