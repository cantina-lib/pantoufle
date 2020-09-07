//
// waaaaahhhhh
//

#include <cant/pan/controller/MidiWah.hpp>

namespace cant::pan
{
    void MidiWah::beforeControlProcess(const MidiControlInternal &incomingControl)
    {

    }

    void MidiWah::beforeNoteProcess(const MidiNoteInternal &incomingNote)
    {

    }

    MidiWah::
    MidiWah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah)
    : MultiMidiController(numberVoices, channel, wahwah)
    {

    }

    void
    MidiWah::
    IMPL_process(MidiNoteInternal &note) const
    {

    }

    void
    MidiWah::
    update(time_d tCurrent)
    {
        MultiMidiController::update(tCurrent);
    }

    UPtr<MidiController>
    MidiWah::
    wah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah)
    {
        return cant::UPtr<MidiController>(new MidiWah(numberVoices, channel, wahwah));
    }
}
