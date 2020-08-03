//
// Created by piptouque on 30/04/2020.
//
#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{
    ToneEnvelope::
    ToneEnvelope(const size_m numberVoices)
    : MidiEnvelope<tone_m>(numberVoices)
    {

    }

    VelocityEnvelope::
    VelocityEnvelope(const size_m numberVoices)
    : MidiEnvelope<vel_m>(numberVoices)
    {

    }
}
