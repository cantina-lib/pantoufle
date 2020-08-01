//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatEnvelope.hpp>

namespace cant::pan
{

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    make()
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope());
    }


    void
    FlatToneEnvelope::
    apply(time_m tCurrent, MidiNoteInternal &note) const
    {
        /* nothing to doooo */
    }
}

