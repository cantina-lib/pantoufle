//
// Created by binabik on 05/06/2020.
//

#include <cant/pan/controller/MidiDamper.hpp>

namespace cant::pan
{
    MidiDamper::
    MidiDamper(const size_m numberVoices, const byte_m channelId, const byte_m controllerId)
    : MidiController(numberVoices, channelId, controllerId),
    _flagShouldHold(false)
    {

    }


    bool
    MidiDamper::
    isOn() const
    {
          return isOn(getControl());
    }

    bool
    MidiDamper::
    isOn(const MidiControlInternal &control)
    {
        return control.getValue() > MIDI_MID_VALUE;
    }

    void
    MidiDamper::
    beforeControlChange(const MidiControlInternal& incoming)
    {
        /*
         * Control is not yet updated,
         * so we compare with the incoming control.
         */
        _flagShouldHold &= isOn(incoming);
    }

    void
    MidiDamper::
    beforeNoteChange(const size_m iVoice, const MidiNoteInternal& incoming)
    {
        _flagShouldHold = isOn() && (getMemory(iVoice).isPlaying() || incoming.isPlaying());
    }

    void
    MidiDamper::
    IMPL_processVoice(const size_m iVoice, MidiNoteInternal &note) const
    {
        note.setChanged(note.justChanged() || _flagShouldHold);
        note.setPlaying(note.isPlaying() || _flagShouldHold);
    }

    void
    MidiDamper::
    update(time_m tCurrent)
    {
        /* nothing to d-d-d-dd-dooo */
    }

    UPtr<MidiController>
    MidiDamper::
    make(const size_m numberVoices, const byte_m channelId, const byte_m controllerId)
    {
        return UPtr<MidiController>(new MidiDamper(numberVoices, channelId, controllerId));
    }


}