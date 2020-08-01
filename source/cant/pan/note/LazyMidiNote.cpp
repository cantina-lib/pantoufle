//
// Created by binabik on 20/07/2020.
//

#include <cant/pan/note/LazyMidiNote.hpp>

namespace cant::pan
{

    UPtr<MidiNote>
    LazyMidiNote::
    IMPL_clone() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return make();
    }

    bool
    LazyMidiNote::
    justChanged() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return hasBaseJustChanged();
    }

    bool
    LazyMidiNote::
    isExtensible() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return isBaseExtensible();
    }

    bool
    LazyMidiNote::
    isPlaying() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return isBasePlaying();
    }

    tone_m
    LazyMidiNote::
    getTone() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return getBaseTone();
    }

    vel_m
    LazyMidiNote::
    getVelocity() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Base not set.");
        }
        return getBaseVelocity();
    }

    UPtr<LazyMidiNote>
    LazyMidiNote::
    make()
    {
        return cant::UPtr<LazyMidiNote>();
    }
}
