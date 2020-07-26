//
// Created by binabik on 30/05/2020.
//

#include <cant/formatting.hpp>

#include <cant/pan/note/EnvelopedMidiNote.hpp>
#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/PantoufleException.hpp>

namespace cant::midi
{
    UPtr<MidiNote>
    EnvelopedMidiNote::
    IMPL_clone() const
    {
        return UPtr<MidiNote>(new EnvelopedMidiNote(_toneEnv, _velEnv, getBase()));
    }

    EnvelopedMidiNote::
    EnvelopedMidiNote(
            const UPtr<ToneEnvelope>& toneEnv,
            const UPtr<VelocityEnvelope>& velEnv)
            : DecoratedMidiNote()
    {
        if(!toneEnv || !velEnv)
        {
            throw PANTOUFLE_EXCEPTION("Envelopes should be set before being assigned to a note.");
        }
        _toneEnv = toneEnv->clone();
        _velEnv  = velEnv->clone();
    }

    EnvelopedMidiNote::
    EnvelopedMidiNote(const UPtr<ToneEnvelope> &toneEnv, const UPtr<VelocityEnvelope> &velEnv, const UPtr<MidiNote>& note)
            : DecoratedMidiNote(note)
    {
        if(!toneEnv || !velEnv)
        {
            throw PANTOUFLE_EXCEPTION("Envelopes should be set before being assigned to a note.");
        }
        _toneEnv = toneEnv->clone();
        _velEnv = velEnv->clone();
    }

    EnvelopedMidiNote::
    EnvelopedMidiNote(const EnvelopedMidiNote& envNote)
    : EnvelopedMidiNote(envNote._toneEnv, envNote._velEnv, envNote.getBase())
    {

    }

    UPtr<MidiNote>
    EnvelopedMidiNote::
    make(const UPtr<ToneEnvelope>& toneEnv, const UPtr<VelocityEnvelope>& velEnv)
    {
        PANTOUFLE_TRY_RETHROW({
             return UPtr<MidiNote>(new EnvelopedMidiNote(toneEnv, velEnv));
        })
    }

    bool
    EnvelopedMidiNote::
    isSet() const
    {
        return isBaseSet();
    }

    bool
    EnvelopedMidiNote::
    justChanged() const
    {
        PANTOUFLE_TRY_RETHROW({
             return _velEnv->justChanged(this);
        })
    }

    vel_m
    EnvelopedMidiNote::
    getVelocity() const
    {
        PANTOUFLE_TRY_RETHROW({
             return _velEnv->operator()(this);
        })
    }

    tone_m
    EnvelopedMidiNote::
    getTone() const
    {
        PANTOUFLE_TRY_RETHROW({
             return _toneEnv->operator()(this);
        })
    }

    bool
    EnvelopedMidiNote::
    isPlaying() const
    {
        PANTOUFLE_TRY_RETHROW({
             return _velEnv->isPlaying(this);
        })
    }

    void
    EnvelopedMidiNote::
    updateEnvelopes(time_m tCurrent)
    {
        _toneEnv->update(this, tCurrent);
        _velEnv->update(this, tCurrent);
    }

    void
    EnvelopedMidiNote::
    resetEnvelopes()
    {
        _toneEnv->reset(this);
        _velEnv->reset(this);
    }

    void EnvelopedMidiNote::update(const UPtr<MidiNote> &base)
    {
        DecoratedMidiNote::update(base);
    }

    void
    EnvelopedMidiNote::
    update(const time_m tCurrent)
    {
        /*
         * IMPORTANT
         * We should update the envelopes !before! the base
         * Because if the base has just changed
         * there's a MidiNoteInput somewhere which will reset its flag when updated!!
         * so update the envelopes with the potential justChanged(),
         * then discard the changed state!
         */
        PANTOUFLE_TRY_RETHROW({
             updateEnvelopes(tCurrent);
             DecoratedMidiNote::update(tCurrent);
        })

    }

    void
    EnvelopedMidiNote::
    reset(const UPtr<MidiNote>& note)
    {
        PANTOUFLE_TRY_RETHROW({
             DecoratedMidiNote::reset(note);
             resetEnvelopes();
        })
    }

    void
    EnvelopedMidiNote::
    reset()
    {
        PANTOUFLE_TRY_RETHROW({
             DecoratedMidiNote::reset();
             resetEnvelopes();
        })
    }

    std::string
    EnvelopedMidiNote::
    print() const
    {
        std::stringstream stream;
        stream << "[enveloped] { [" << _velEnv << ", " << _toneEnv << "], ";
        stream << DecoratedMidiNote::print() << " }";
        return stream.str();
    }
}

