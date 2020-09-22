//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatToneEnvelope.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    make()
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope());
    }


    void
    FlatToneEnvelope::
    process(CANT_MAYBEUNUSED MidiNoteInternal &note)
    {
        /* nothing to doooo */
    }

    void
    FlatToneEnvelope::
    updateDelta(time_d)
    {

    }

CANTINA_PAN_NAMESPACE_END
