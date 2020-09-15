//
// Created by piptouque on 28/04/2020.
//

#ifndef PANTOUFLEENVELOPE_HPP
#define PANTOUFLEENVELOPE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    /**
     * Envelopes should not have internal states
     * but compute everything from input note (contains starting time)
     * and current time.
     **/
    template <typename T>
    class MidiEnvelope : public MidiProcessorMemory
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiEnvelope(size_u numberVoices);

        void update(time_d tCurrent) override;
        void process(MidiNoteInternal& note) override = 0;

        virtual void flushChange() = 0;
    protected:
        /** -- methods -- **/
        CANT_NODISCARD time_d getCurrentTime() const;
    private:
        /** -- fields -- **/
        time_d m_tCurrent;
    };


    class ToneEnvelope : public MidiEnvelope<tone_d>
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT ToneEnvelope(size_u numberVoices);

        void process(MidiNoteInternal& note) override = 0;

        void flushChange() override = 0;
    };


    class VelocityEnvelope : public MidiEnvelope<vel_d>
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT VelocityEnvelope(size_u numberVoices);

        void process(MidiNoteInternal& note) override = 0;

        void flushChange() override = 0;
    };
}
#include <cant/common/undef_macro.hpp>

#include "../../../../inline/cant/pan/envelope/MidiEnvelope.inl"

#endif //PANTOUFLEENVELOPE_HPP
