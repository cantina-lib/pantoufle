//
// Created by piptouque on 30/04/2020.
//
#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{
    UPtr<ToneEnvelope>
    ToneEnvelope::
    clone() const
    {
        PANTOUFLE_TRY_RETHROW({
           return Cloneable::clone();
        })
    }


    UPtr<VelocityEnvelope>
    VelocityEnvelope::
    clone() const
    {
        PANTOUFLE_TRY_RETHROW({
            return Cloneable::clone();
        })
    }

    VelocityEnvelope::
    VelocityEnvelope()
    : _flagChanged(false)
    {

    }

    bool
    VelocityEnvelope::
    justChanged(const EnvelopedMidiNote* envNote) const
    {
        PANTOUFLE_TRY_RETHROW({
             return _flagChanged || envNote->hasBaseJustChanged();
        })
    }

    bool
    VelocityEnvelope::
    isPlaying(const EnvelopedMidiNote* envNote) const
    {
        if(!MidiNote::isNoteSet(envNote))
        {
            return false;
        }
        PANTOUFLE_TRY_RETHROW({
             bool envelopePlaying = isEnvelopePlaying();
             if(envNote->isBaseExtensible())
             {
                 /*
                  * if base note can be extended (ie: Raw)
                  */
                 return envelopePlaying;
             }
             return envelopePlaying && envNote->isBasePlaying();
        })
    }

    void
    VelocityEnvelope::
    IMPL_update(const EnvelopedMidiNote* envNote)
    {
        discardFlagChanged();
        IMPL_Velocity_update(envNote);
    }

    void
    VelocityEnvelope::
    IMPL_reset()
    {
        raiseFlagChanged();
        IMPL_Velocity_reset();
    }

    void
    VelocityEnvelope::
    raiseFlagChanged()
    {
        _flagChanged = true;
    }

    void
    VelocityEnvelope::
    discardFlagChanged()
    {
        _flagChanged = false;
    }

    vel_m
    VelocityEnvelope::
    operator()(const EnvelopedMidiNote* envNote) const
    {
        /* */
        PANTOUFLE_TRY_RETHROW(
        {
            float_m velocityRatio = getVelocityRatio();
            return velocityRatio * envNote->getBaseVelocity();
        })
    }

    tone_m
    ToneEnvelope::
    operator()(const EnvelopedMidiNote* envNote) const
    {
        PANTOUFLE_TRY_RETHROW({
            return getToneProcessed(envNote);
        })
    }

    std::ostream&
    operator<<(std::ostream& out, CANT_MAYBEUNUSED const ToneEnvelope* env)
    {
        CANTINA_ASSERT(env)
        out << "[toneenv] ";
        return out;
    }

    std::ostream&
    operator<<(std::ostream& out, const UPtr<ToneEnvelope>& env)
    {
        return out << env.get();
    }


    std::ostream&
    operator<<(std::ostream& out, CANT_MAYBEUNUSED const VelocityEnvelope* env)
    {
        CANTINA_ASSERT(env)
        out << "[velenv] ";
        out << env->print();
        return out;
    }

    std::ostream&
    operator<<(std::ostream& out, const UPtr<VelocityEnvelope>& env)
    {
        return out << env.get();
    }

}
