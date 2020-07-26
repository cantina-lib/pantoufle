//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDISTREAM_HPP
#define CANTINA_MIDISTREAM_HPP

#pragma once


#include <cant/common/formatting.hpp>

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>
#include <cant/common/macro.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/RawMidiNote.hpp>
#include <cant/pan/note/EnvelopedMidiNote.hpp>
#include <cant/pan/control/MidiControl.hpp>



namespace cant::midi
{
    /* todo: create wrapper class to handle exceptions and transformations. */
    class MidiController;

    /*
     * TODO: make UStream derive from std::vector with added functionalities
     * rather than add the below functions
     * */

    template <typename T>
    using UStream = Stream<UPtr<T>>;

    template <typename T>
    using ShStream = Stream<ShPtr<T>>;

    template <typename Key_T, typename Val_T>
    using UMap = Map<Key_T, UPtr<Val_T>>;

    template <class Note_T>
    void updateMidiNoteStream(UStream<Note_T>& stream, const time_m tCurrent)
    {
        static_assert(std::is_base_of<MidiNote, Note_T>::value, "Nooooo");
        for (auto& note : stream)
        {
            if (MidiNote::isNoteSet(note))
            {
                PANTOUFLE_TRY_RETHROW({
                    note->update(tCurrent);
                })
            }
        }
    }



    /*
     * TODO: not sure it should be template, MidiNote ought to be enough
     * but we do handle ControlledMidiNote smart pointers in MidiController...
     */
    template <typename Note_T>
    std::ostream& operator<<(std::ostream& out, const UStream<Note_T>& noteStream)
    {
        static_assert(std::is_base_of<MidiNote, Note_T>::value, "Nooooo");

        out << "[STREAM] - " << CANT_RUNTIME_TYPE_NAME(Note_T) << std::endl;
        for(const auto& note : noteStream)
        {
            out << note << std::endl;
        }

        return out;
    }


}

#endif //CANTINA_MIDISTREAM_HPP
