//
// waaaaahhhhh
//

#include <cant/pan/controller/MidiWah.hpp>

namespace cant::pan
{
    void MidiWah::beforeControlProcess(const MidiControlInternal &)
    {

    }

    void MidiWah::beforeNoteProcess(const MidiNoteInternal &)
    {

    }

    MidiWah::
    MidiWah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah)
    : MultiMidiController(numberVoices, channel, wahwah)
    {

    }

    void
    MidiWah::
    IMPL_process(MidiNoteInternal &) const
    {

    }

    void
    MidiWah::
    update(const time_d)
    {

    }

    UPtr<MidiController>
    MidiWah::
    wah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah)
    {
        return cant::UPtr<MidiController>(new MidiWah(numberVoices, channel, wahwah));
    }
}
