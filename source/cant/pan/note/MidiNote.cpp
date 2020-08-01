//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/pan/note/MidiNote.hpp>

#include <cant/pan/note/RawMidiNote.hpp>

namespace cant::pan
{

    MidiNoteOutput
    MidiNote::
    getOutput() const
    {
        return MidiNoteOutput(
                getTone(),
                getVelocity(),
                getChannel(),
                isPlaying(),
                justChanged()
        );
    }

    UPtr<MidiNote>
    MidiNote::
    clone() const
    {
        if(!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Source note not set.");
        }
        PANTOUFLE_TRY_RETHROW({
             return Cloneable::clone();
        })
    }

    void
    MidiNote::
    updateElseSet(const UPtr<MidiNote> &src)
    {
        if (!isNoteSet(src))
        {
            throw PANTOUFLE_EXCEPTION("Source note not set.");
        }
        PANTOUFLE_TRY_RETHROW({
             // std::cout << "src: " << src << std::endl;
             if (isSet())
             {
                 update(src->clone());
             }
             else
             {
                 set(src->clone());
             }
             // std::cout << "res: " << this << std::endl;
         })
    }

    bool
    MidiNote::
    isNoteSet(const MidiNote *note)
    {
        return static_cast<bool>(note) && note->isSet();
    }

    bool
    MidiNote::
    justStopped() const
    {
        return !isPlaying() && justChanged();
    }

    bool
    MidiNote::
    justStarted() const
    {
        return isPlaying() && justChanged();
    }

    const UPtr<MidiNote>&
    MidiNote::
    max(const UPtr<MidiNote>& n1, const UPtr<MidiNote>& n2)
    {
        if(!isNoteSet(n1) || !isNoteSet(n2))
        {
            throw PANTOUFLE_EXCEPTION("Note not set");
        }
        return n1->isStronger(n2) ? n1 : n2;
    }

    bool
    MidiNote::
    isDifferent(const UPtr<MidiNote>& note) const
    {
        if(!isNoteSet(note))
        {
            throw PANTOUFLE_EXCEPTION("Note not set");
        }
        return getInputData().getTone() != note->getInputData().getTone();
    }

    bool
    MidiNote::
    isStronger(const UPtr<MidiNote>& note) const
    {
        if(!isNoteSet(note))
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        return getInputData().getVelocity() > note->getInputData().getVelocity();
    }

    std::ostream&
    operator<<(std::ostream& out, const MidiNote* note)
    {
        out << "[midinote]";
        if(!MidiNote::isNoteSet(note))
        {
            out << "[NOTSET]";
            return out;
        }
        out << note->print();
        out << (note->isPlaying() ? " [PLAYING]" : " [STOPPED]");
        out <<  (note->justChanged() ? " !CHANGE" : "");
        return out;
    }
}

