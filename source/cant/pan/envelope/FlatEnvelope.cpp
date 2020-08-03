//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatEnvelope.hpp>

namespace cant::pan
{

    FlatToneEnvelope::
    FlatToneEnvelope(const size_m numberVoices)
    : ToneEnvelope(numberVoices)
    {

    }

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    make(const size_m numberVoices)
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope(numberVoices));
    }


    void
    FlatToneEnvelope::
    processVoice(size_m iVoice, MidiNoteInternal &note)
    {
        /* nothing to doooo */
    }

    void
    FlatToneEnvelope::
    flushChange()
    {

    }
}

