//
// Created by binabik on 08/08/2020.
//

#include <cant/pan/controller/MidiPan.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiPan::
    MidiPan(size_u numberVoices, id_u8 channel, id_u8 controllerId)
    : MultiMidiController<1>(numberVoices, channel, { controllerId })
    {

    }

    void
    MidiPan::
    beforeControlProcess(const MidiControlInternal &)
    {

    }

    void
    MidiPan::
    beforeNoteProcess(const MidiNoteInternal &)
    {

    }

    pan_d
    MidiPan::
    getPan() const
    {
        return (getControl(0).getValue() / static_cast<pan_d>(c_midiControlMidValue)) * 2 - 1;
    }

    void
    MidiPan::
    IMPL_process(MidiNoteInternal &note) const
    {
        note.setPan(getPan());
    }

    void
    MidiPan::
    update(const time_d)
    {

    }

    UPtr<MidiController>
    MidiPan::
    make(size_u numberVoices, id_u8 channel, id_u8 controllerId)
    {
        return cant::UPtr<MidiController>(new MidiPan(numberVoices, channel, controllerId));
    }

CANTINA_PAN_NAMESPACE_END