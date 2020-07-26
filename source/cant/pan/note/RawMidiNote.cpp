//
// Created by binabik on 02/06/2020.
//

#include <cant/pan/note/RawMidiNote.hpp>

#include <cant/pan/PantoufleException.hpp>

#include <cant/formatting.hpp>


namespace cant::midi
{

    RawMidiNote::
    RawMidiNote(const MidiNoteInput& input)
    : _input(input),
      _flagSet(true)
    {
    }

    UPtr<MidiNote>
    RawMidiNote::
    IMPL_clone() const
    {
        return UPtr<MidiNote>(new RawMidiNote(*this));
    }

    tone_m
    RawMidiNote::
    getTone() const
    {
        return _input.getTone();
    }

    vel_m
    RawMidiNote::
    getVelocity() const
    {
        return _input.getVelocity();
    }


    byte_m
    RawMidiNote::
    getChannel() const
    {
        return _input.getChannel();
    }

    time_m
    RawMidiNote::
    getStartingTime() const
    {
        return _input.getStartingTime();
    }

    const MidiNoteInput&
    RawMidiNote::
    getInputData() const
    {
        return _input;
    }

    bool
    RawMidiNote::
    isPressed() const
    {
        return _input.isPressed();
    }

    bool
    RawMidiNote::
    isPlaying() const
    {
        return isPressed();
    }

    bool
    RawMidiNote::
    isSet() const
    {
        return _flagSet;
    }

    bool
    RawMidiNote::
    justChanged() const
    {
        return _input.justChanged();
    }

    void
    RawMidiNote::
    set(const UPtr<MidiNote> &note)
    {
        PANTOUFLE_TRY_RETHROW({
            _input = note->getInputData();
        })
        _flagSet = true;
    }

    void
    RawMidiNote::
    update(const UPtr<MidiNote> &note)
    {
        /* only if playing and new */
        PANTOUFLE_TRY_RETHROW({
             if(isNew(note))
             {
                 reset(note);
             }
             else if(isPlaying() && !note->isPlaying())
             {
                 // not playing any more!
                 reset();
             }
        })
    }

    void
    RawMidiNote::
    update(const time_m tCurrent)
    {
        _input.update(tCurrent);
    }

    UPtr<MidiNote>
    RawMidiNote::
    make(const MidiNoteInput &input)
    {
        return UPtr<MidiNote>(new RawMidiNote(input));
    }

    bool
    RawMidiNote::
    isNew(const UPtr<MidiNote>& note) const
    {
        PANTOUFLE_TRY_RETHROW({
             if(!note->isPlaying())
             {
                 return false;
             }
             return isPlaying() ? isDifferent(note) : true;
        })
    }


    void
    RawMidiNote::
    reset(const UPtr<MidiNote>& note)
    {
        PANTOUFLE_TRY_RETHROW({
             set(note);
        })

    }

    void
    RawMidiNote::
    reset()
    {
        // nothing
    }

    std::string
    RawMidiNote::
    print() const
    {
        std::stringstream stream;
        stream << "[raw] { " << getInputData() << " }";
        return stream.str();
    }
}

