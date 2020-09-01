//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDIPROCESSOR_HPP
#define CANTINA_MIDIPROCESSOR_HPP

#pragma once

#include <cant/common/types.hpp>
#include <cant/common/memory.hpp>

#include <cant/pan/layer/MidiNoteLayer.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiProcessor
    {
    public:
        /** -- methods -- **/
        virtual void update(time_m tCurrent) = 0;
        virtual void process(MidiNoteInternal& in) = 0;
    };

    class MidiProcessorMemory : public MidiProcessor
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiProcessorMemory(size_m numberVoices);
        virtual ~MidiProcessorMemory() = default;

        void update(time_m tCurrent) override = 0;
        void process(MidiNoteInternal& in) override = 0;

        CANT_NODISCARD size_m getNumberVoices() const;
    protected:
        /** -- fields -- **/
        MidiNoteInternalLayer m_memory;
    };
}

#include <cant/common/undef_macro.hpp>

#include "MidiProcessor.inl"

#endif //CANTINA_MIDIPROCESSOR_HPP
