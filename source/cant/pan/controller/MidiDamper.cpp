//
// Created by binabik on 05/06/2020.
//

#include <cant/pan/controller/MidiDamper.hpp>

namespace cant::pan
{
    MidiDamper::
    MidiDamper(const size_m numberVoices, const byte_m channelId, const byte_m controllerId)
    : MidiController(numberVoices, channelId, controllerId),
      _shouldHoldNotes(numberVoices, false)
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
    beforeControlProcess(const MidiControlInternal& incomingControl)
    {
        /*
         * Control is not yet updated,
         * so we compare with the incoming control.
         */
        for (auto& shouldHold : _shouldHoldNotes)
        {
            shouldHold = static_cast<byte_m>(
                    static_cast<bool>(shouldHold)
                    && isOn(incomingControl)
                    );
        }
    }

    void
    MidiDamper::
    beforeNoteProcess(const size_m iVoice, const MidiNoteInternal& incomingNote)
    {
        _shouldHoldNotes.at(iVoice) = static_cast<byte_m>(
                isOn()
                && (getMemory(iVoice).isPlaying() || incomingNote.isPlaying())
                );
    }

    void
    MidiDamper::
    IMPL_processVoice(const size_m iVoice, MidiNoteInternal &note) const
    {
        const bool shouldHold = static_cast<bool>(_shouldHoldNotes.at(iVoice));
        note.setPlaying(note.isPlaying() || shouldHold);
        /*
         * After setting the playing state to it
         * the note can be compared to the last processed one (memory)
         * to decide whether it has changed.
         * It's pretty overkill, but it gets the work done.
         */
        note.setChangedPlaying(note.isPlaying() != getMemory(iVoice).isPlaying());
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