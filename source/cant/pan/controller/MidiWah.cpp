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
    MidiWah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah)
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
    update(time_m tCurrent)
    {
        MultiMidiController::update(tCurrent);
    }

    UPtr<MidiController>
    MidiWah::
    wah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah)
    {
        return cant::UPtr<MidiController>(new MidiWah(numberVoices, channel, wahwah));
    }
}
