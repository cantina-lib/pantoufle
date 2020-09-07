//
// Created by piptouque on 30/04/2020.
//
#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{
    ToneEnvelope::
    ToneEnvelope(const size_u numberVoices)
    : MidiEnvelope<tone_d>(numberVoices)
    {

    }

    VelocityEnvelope::
    VelocityEnvelope(const size_u numberVoices)
    : MidiEnvelope<vel_d>(numberVoices)
    {

    }
}
