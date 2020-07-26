//
// Created by binabik on 04/06/2020.
//

#include <cant/pan/note/DecoratedMidiNote.hpp>

namespace cant::midi
{
    DecoratedMidiNote::
    DecoratedMidiNote(const UPtr<MidiNote>& base)
    : _base(base->clone())
    {
        if(!isNoteSet(base))
        {
            throw PANTOUFLE_EXCEPTION("Note should be set before being assigned.");
        }
    }

    DecoratedMidiNote::
    DecoratedMidiNote(const DecoratedMidiNote& decNote)
    : DecoratedMidiNote(decNote._base)
    {
        if(!decNote.isSet())
        {
            throw PANTOUFLE_EXCEPTION("Note should be set before being copied.");
        }
    }

    const UPtr<MidiNote>&
    DecoratedMidiNote::
    getBase() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base Note not set.");
        }
        return _base;
    }

    void
    DecoratedMidiNote::
    setBase(const UPtr <MidiNote> &base)
    {
        if(!isNoteSet(base))
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        _base = base->clone();
    }

    void
    DecoratedMidiNote::
    set(const UPtr<MidiNote> &base)
    {
        if(!isNoteSet(base))
        {
            throw PANTOUFLE_EXCEPTION("Base Note not set.");
        }
        reset(base);
    }

    bool
    DecoratedMidiNote::
    isNew(const UPtr<MidiNote>& note) const
    {
        if(!isNoteSet(note))
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        bool noteIsNew = isBaseSet() ? _base->isNew(note) : true;
        return noteIsNew;
    }

    bool
    DecoratedMidiNote::
    isPressed() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->isPressed();
    }

    bool
    DecoratedMidiNote::
    isBaseSet() const
    {
        return MidiNote::isNoteSet(_base);
    }

    bool
    DecoratedMidiNote::
    isSet() const
    {
        return isBaseSet();
    }

    bool
    DecoratedMidiNote::
    isBasePlaying() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->isPlaying();
    }

    const MidiNoteInput&
    DecoratedMidiNote::
    getInputData() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->getInputData();
    }

    time_m
    DecoratedMidiNote::
    getStartingTime() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->getStartingTime();
    }

    vel_m
    DecoratedMidiNote::
    getBaseVelocity() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base Note not set.");
        }
        return _base->getVelocity();
    }

    tone_m
    DecoratedMidiNote::
    getBaseTone() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->getTone();
    }


    bool
    DecoratedMidiNote::
    hasBaseJustStarted() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->justStarted();
    }

    bool
    DecoratedMidiNote::
    hasBaseJustStopped() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->justStopped();
    }

    bool
    DecoratedMidiNote::
    hasBaseJustChanged() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->justChanged();
    }

    void
    DecoratedMidiNote::
    update(const UPtr<MidiNote> &base)
    {
        if(!isNoteSet(base))
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        setBase(base);
    }

    void
    DecoratedMidiNote::
    update(const time_m tCurrent)
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        _base->update(tCurrent);
    }

    void
    DecoratedMidiNote::
    reset(const UPtr<MidiNote>& base)
    {
        if(!isNoteSet(base))
        {
            throw PANTOUFLE_EXCEPTION("Note not set.");
        }
        setBase(base);
    }

    void
    DecoratedMidiNote::
    reset()
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        _base->reset();
    }

    bool
    DecoratedMidiNote::
    isBaseExtensible() const
    {
        if(!isBaseSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return _base->isExtensible();
    }

    byte_m
    DecoratedMidiNote::
    getChannel() const
    {
        if(!isBaseSet())
        {
        }
        return _base->getChannel();
    }

    std::string
    DecoratedMidiNote::
    print() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Decorated note not set.");
        }
        return _base->print();
    }
}

