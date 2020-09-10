//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatEnvelope.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    FlatToneEnvelope::
    FlatToneEnvelope(const size_u numberVoices)
    : ToneEnvelope(numberVoices)
    {

    }

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    make(const size_u numberVoices)
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope(numberVoices));
    }


    void
    FlatToneEnvelope::
    process(CANT_MAYBEUNUSED MidiNoteInternal &note)
    {
        /* nothing to doooo */
    }

    void
    FlatToneEnvelope::
    flushChange()
    {

    }
}

