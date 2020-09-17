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
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiProcessor
    {
    public:
        /** -- methods -- **/
        virtual ~MidiProcessor() = default;

        virtual void update(time_d tCurrent) = 0;
        virtual void process(MidiNoteInternal& in) = 0;
    };

    class MidiProcessorMemory : public MidiProcessor
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiProcessorMemory(size_u numberVoices);

        void update(time_d tCurrent) override = 0;
        void process(MidiNoteInternal& in) override = 0;

        CANT_NODISCARD size_u getNumberVoices() const;
    protected:
        /** -- fields -- **/
        MidiNoteInternalLayer m_memory;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include "../../../../inline/cant/pan/processor/MidiProcessor.inl"

#endif //CANTINA_MIDIPROCESSOR_HPP
