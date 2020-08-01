//
// Created by binabik on 04/06/2020.
//

#include <cant/pan/note/DampMidiNote.hpp>

namespace cant::pan
{

    DampMidiNote::
    DampMidiNote(WPtr<MidiControl> control)
    : ControlledMidiNote(std::move(control)),
      _flagShouldHold(false)
    {

    }

    UPtr<MidiNote>
    DampMidiNote::
    IMPL_clone() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Note (or control) not set.");
        }
        return UPtr<MidiNote>(new DampMidiNote(*this));
    }



    bool
    DampMidiNote::
    isOn() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Note not set");
        }
        PANTOUFLE_TRY_RETHROW({
            const auto& sharedControl = getControl().lock();
            if (!sharedControl)
            {
                throw PANTOUFLE_EXCEPTION("Control expired.");
                return false;
            }
            const byte_m val = sharedControl->getValue();
            return val > MIDI_MID_VALUE;
        })
    }

    void
    DampMidiNote::
    onControlChange()
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Damp pan note not set.");
        }
        _flagShouldHold &= isOn();
    }

    void
    DampMidiNote::
    set(const UPtr<MidiNote> &baseNote)
    {
        PANTOUFLE_TRY_RETHROW({
            DecoratedMidiNote::set(baseNote);
        })
    }

    void
    DampMidiNote::
    update(const UPtr<MidiNote> &baseNote)
    {
        PANTOUFLE_TRY_RETHROW({
             _flagShouldHold = isOn() && (isBasePlaying() || baseNote->isPlaying());
             DecoratedMidiNote::update(baseNote);
        })
    }

    bool
    DampMidiNote::
    justChanged() const
    {
        PANTOUFLE_TRY_RETHROW({
             if (_flagShouldHold)
             {
                 return hasBaseJustStarted();
             }
             else
             {
                 return hasBaseJustChanged();
             }
        })
    }


    bool
    DampMidiNote::
    isPlaying() const
    {
        PANTOUFLE_TRY_RETHROW({
             return _flagShouldHold || isBasePlaying();
        })
    }

    tone_m
    DampMidiNote::
    getTone() const
    {
        PANTOUFLE_TRY_RETHROW({
             return getBaseTone();
        })
    }

    vel_m
    DampMidiNote::
    getVelocity() const
    {
        /* if isOn(), then getPlayingVelocity will be zero */
        PANTOUFLE_TRY_RETHROW({
             return getBaseVelocity();
        })
    }

    UPtr<ControlledMidiNote>
    DampMidiNote::
    make(WPtr<MidiControl> control)
    {
        return UPtr<ControlledMidiNote>(new DampMidiNote(std::move(control)));
    }

    std::string
    DampMidiNote::
    print() const
    {
        return "[damp] { " + ControlledMidiNote::print() + ' ' + std::to_string(_flagShouldHold) + ' ' + " }";
    }


}
