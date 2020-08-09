//
// Created by binabik on 08/08/2020.
//

#include <cant/pan/controller/MidiPan.hpp>

namespace cant::pan
{
    MidiPan::
    MidiPan(size_m numberVoices, byte_m channel, byte_m controllerId)
    : MultiMidiController<1>(numberVoices, channel, { controllerId })
    {

    }

    void MidiPan::beforeControlProcess(const MidiControlInternal &incomingControl)
    {

    }

    void MidiPan::beforeNoteProcess(const MidiNoteInternal &incomingNote)
    {

    }


    pan_m MidiPan::getPan() const
    {
        return (getControl(0).getValue() / static_cast<pan_m>(MIDI_CONTROL_MID_VALUE)) * 2 - 1;
    }

    void MidiPan::IMPL_process(MidiNoteInternal &note) const
    {
        note.setPan(getPan());
    }

    void MidiPan::update(time_m tCurrent)
    {

    }

    UPtr<MidiController> MidiPan::make(size_m numberVoices, byte_m channel, byte_m controllerId)
    {
        return cant::UPtr<MidiController>(new MidiPan(numberVoices, channel, controllerId));
    }
}
