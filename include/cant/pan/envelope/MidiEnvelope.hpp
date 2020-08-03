//
// Created by piptouque on 28/04/2020.
//

#ifndef PANTOUFLEENVELOPE_HPP
#define PANTOUFLEENVELOPE_HPP

#pragma once


#include <cant/common/formatting.hpp>
#include <cant/pan/common/types.hpp>
#include <cant/pan/common/MidiTimer.hpp>

#include <cant/pan/note/MidiNote.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

namespace cant::pan
{

    /**
     * Envelopes should not have internal states
     * but compute everything from input note (contains starting time)
     * and current time.
     **/
    template <typename T>
    class MidiEnvelope : MidiProcessorMemory
    {
    private:
        time_m _tCurrent;
    protected:
        CANT_NODISCARD time_m getCurrentTime() const
        {
            return _tCurrent;
        }
    public:
        CANT_EXPLICIT MidiEnvelope(size_m numberVoices)
        : MidiProcessorMemory(numberVoices),
        _tCurrent()
        {

        }

        // envelopes are state-less, so const here
        // TODO noooo, it needs a state
        void update(const time_m tCurrent) override
        {
            _tCurrent = tCurrent;
        }
        void processVoice(size_m iVoice, MidiNoteInternal& note) override = 0;

        virtual void flushChange() = 0;
    };

    class ToneEnvelope : public MidiEnvelope<tone_m>
    {
    public:
        CANT_EXPLICIT ToneEnvelope(size_m numberVoices);
        void processVoice(size_m iVoice, MidiNoteInternal& note) override = 0;

        void flushChange() = 0;
    };


    class VelocityEnvelope : public MidiEnvelope<vel_m>
    {
    public:
        CANT_EXPLICIT VelocityEnvelope(size_m numberVoices);
        void processVoice(size_m iVoice, MidiNoteInternal& note) override = 0;

        void flushChange() = 0;
    };
}

#endif //PANTOUFLEENVELOPE_HPP
