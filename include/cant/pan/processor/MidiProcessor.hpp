//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDIPROCESSOR_HPP
#define CANTINA_MIDIPROCESSOR_HPP

#pragma once

#include <cant/pan/stream/MidiStream.hpp>
#include <cant/pan/note/MidiNote.hpp>

namespace cant::midi
{
    class MidiProcessor
    {

    public:
        virtual ~MidiProcessor() = default;

        CANT_NODISCARD CANT_INLINE virtual sizeint getNumberVoices() const = 0;

        CANT_NODISCARD virtual  const UPtr<MidiNote>& getProcessed(sizeint iVoice) const = 0;

        virtual void update(time_m tCurrent) = 0;

        virtual void processVoice(sizeint iVoice, const UPtr<MidiNote>& in) = 0;
    };

    class MidiProcessorMemory : public MidiProcessor
    {
    protected:
        UStream<MidiNote> _processed;
    public:
        CANT_EXPLICIT MidiProcessorMemory(const sizeint numberVoices) : _processed(numberVoices)
        {

        }

        CANT_NODISCARD CANT_INLINE
        sizeint getNumberVoices() const final { return _processed.size(); }

        CANT_NODISCARD const UPtr<MidiNote>& getProcessed(const sizeint iVoice) const final
        {
            return _processed.at(iVoice);
        }

        void
        update(const time_m tCurrent) override
        {
            updateMidiNoteStream(_processed, tCurrent);
        }
    };

    template <class Note_T>
    class MidiProcessorMemoryProxy : public MidiProcessor
    {
    protected:
        UStream<Note_T> _processed;
        mutable UStream<MidiNote> _processedProxy;
    public:
        CANT_EXPLICIT MidiProcessorMemoryProxy(const sizeint numberVoices)
        : _processed(numberVoices), _processedProxy(numberVoices)
        {
            static_assert(std::is_base_of<MidiNote, Note_T>::value);
        }

        CANT_NODISCARD CANT_INLINE
        sizeint getNumberVoices() const final { return _processed.size(); }

        void
        update(const time_m tCurrent) override
        {
            updateMidiNoteStream(_processed, tCurrent);
        }

        CANT_NODISCARD const UPtr<MidiNote>& getProcessed(const sizeint iVoice) const final
        {
            auto& note = _processedProxy.at(iVoice);
            note = _processed.at(iVoice)->clone();
            return note;
        }



    };
}

#endif //CANTINA_MIDIPROCESSOR_HPP
