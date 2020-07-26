//
// Created by binabik on 05/06/2020.
//

#include <cant/pan/controller/MidiDamper.hpp>

#include <cant/pan/note/DampMidiNote.hpp>

namespace cant::midi
{
    UPtr<MidiController>
    MidiDamper::
    make(const sizeint numberVoices, const byte_m channelId, const byte_m controllerId)
    {
        return UPtr<MidiController>(new MidiDamper(numberVoices, channelId, controllerId));
    }

    UPtr <ControlledMidiNote>
    MidiDamper::
    allocateNote(const WPtr <MidiControl> &control) const
    {
        return DampMidiNote::make(control);
    }

    MidiDamper::
    MidiDamper(const sizeint numberVoices, const byte_m channelId, const byte_m controllerId)
    : MidiController(numberVoices, channelId, controllerId)
    {
        allocateProcessed();
    }


}