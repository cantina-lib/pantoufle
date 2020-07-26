//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/FlatEnvelope.hpp>

namespace cant::midi
{

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    make()
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope());
    }

    UPtr<ToneEnvelope>
    FlatToneEnvelope::
    IMPL_clone() const
    {
        return UPtr<ToneEnvelope>(new FlatToneEnvelope(*this));
    }

    void
    FlatToneEnvelope::
    IMPL_update(const EnvelopedMidiNote *note)
    {

    }

    void
    FlatToneEnvelope::
    IMPL_reset()
    {

    }

    tone_m
    FlatToneEnvelope::
    getToneProcessed(const EnvelopedMidiNote* note) const
    {
        PANTOUFLE_TRY_RETHROW({
            return note->getBaseTone();
        })
    }
}

