//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDINOTE_HPP
#define CANTINA_MIDINOTE_HPP

#pragma once

#include <iostream>
#include <string>

#include <cant/pan/common/types.hpp>
#include <cant/pan/common/Cloneable.hpp>
#include <cant/pan/common/PantoufleException.hpp>
#include <cant/common/CantinaException.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/pan/note/MidiNoteData.hpp>


namespace cant::pan
{
    class RawMidiNote;
    class DecoratedMidiNote;
    class DampMidiNote;

    class MidiNote : MidiNoteCompatible, Cloneable<MidiNote>
    {
        friend RawMidiNote;
        friend DecoratedMidiNote;
        friend DampMidiNote;
    private:
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override = 0;
        CANT_NODISCARD virtual bool justChanged() const = 0;
        CANT_NODISCARD virtual bool isNew(const UPtr<MidiNote>& note) const = 0;

        CANT_NODISCARD virtual bool isSet() const = 0;


        virtual void set(const UPtr<MidiNote> &note) = 0;

        CANT_NODISCARD virtual std::string print() const { /* todo */ return std::string(); }

    protected:

        CANT_NODISCARD bool isStronger(const UPtr<MidiNote>&) const;
        CANT_NODISCARD bool isDifferent(const UPtr<MidiNote>&) const;

        /*
         * @brief: marks whether the note can be extended by an envelope.
         * Should always be true for RawMidiNote, false for EnvelopedMidiNote
         * */
        CANT_NODISCARD virtual bool isExtensible() const = 0;;
        virtual void update(const UPtr<MidiNote> &) = 0;

        virtual void reset(const UPtr<MidiNote>& note) = 0;
        virtual void reset() = 0;

        CANT_NODISCARD vel_m getVelocity() const override = 0;
        CANT_NODISCARD virtual time_m getStartingTime() const = 0;
        /*
        CANT_ATTR_NODISCARD virtual time_m getRootTone() const = 0;
        CANT_ATTR_NODISCARD virtual vel_m getRootVelocity() const = 0;
         */
        CANT_NODISCARD virtual const MidiNoteInput& getInputData() const = 0;
    public:
        CANT_NODISCARD UPtr<MidiNote> clone() const final;

        void
        updateElseSet(const UPtr<MidiNote> &src);

        template<class Source_T>
        static void clone(UPtr<MidiNote> &dest, const UPtr<Source_T> &src)
        {
            static_assert(std::is_base_of<MidiNote, Source_T>::value, "Source Note should be derived from MidiNote, ya thick.");
            if(!isNoteSet(src))
            {
                throw PANTOUFLE_EXCEPTION("Source note not set.");
            }
            PANTOUFLE_TRY_RETHROW({
                dest = src->clone();
            })
        }


        virtual void update(time_m tCurrent) = 0;


        CANT_NODISCARD static bool isNoteSet(const MidiNote* note);

        template<typename Note_T>
        CANT_NODISCARD static bool isNoteSet(const UPtr<Note_T>& note)
        {
            static_assert(std::is_base_of<MidiNote, Note_T>::value, "Nope.");
            return isNoteSet(note.get());
        }
        /* @returns; the first note if they have the same velocity, otherwise the note with the highest velocity. */
        CANT_NODISCARD static const UPtr<MidiNote>& max(const UPtr<MidiNote>&, const UPtr<MidiNote>&);

        CANT_NODISCARD const MidiNote& operator=(const MidiNote&) = delete;
        CANT_NODISCARD virtual bool isPressed() const = 0;
        CANT_NODISCARD virtual bool isPlaying() const = 0;

        CANT_NODISCARD virtual bool justStarted() const;
        CANT_NODISCARD virtual bool justStopped() const;

        CANT_NODISCARD time_m getTone() const override = 0;
        CANT_NODISCARD byte_m getChannel() const override = 0;

        /* this should be the only output point from Pantoufle */
        CANT_NODISCARD MidiNoteOutput getOutput() const;

        friend std::ostream& operator<<(std::ostream& out, const MidiNote* note);
    };

    template <typename Note_T>
    std::ostream&
    operator<<(std::ostream& out, const UPtr<Note_T>& note)
    {
        static_assert(std::is_base_of<MidiNote, Note_T>::value);
        return out << note.get();
    }

    std::ostream& operator<<(std::ostream& out, const MidiNote* note);

}

#endif //CANTINA_MIDINOTE_HPP
