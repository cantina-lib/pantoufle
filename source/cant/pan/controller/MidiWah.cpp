//
// wah!
//

#include <cant/pan/controller/MidiWah.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    void
    MidiWah::
    beforeControlProcess(const MidiControlInternal &)
    {

    }

    void
    MidiWah::
    beforeNoteProcess(const MidiNoteInternal &)
    {

    }

    MidiWah::
    MidiWah
    (
            size_u numberVoices,
            id_u8 channel,
            Array<id_u8, 2> wahwah,
            const UPtr<MidiTimer>& timer
    )
    : MultiMidiController(numberVoices, channel, wahwah),
    DeltaTimeUpdatable()
    {
        this->subscribe(timer->timeModule.get());
    }

    void
    MidiWah::
    IMPL_process(MidiNoteInternal &) const
    {

    }

    void
    MidiWah::
    updateDelta(const time_d)
    {
        /* todo */

    }

    UPtr<MidiController>
    MidiWah::
    wah
    (
            size_u numberVoices,
            id_u8 channel,
            Array<id_u8, 2> wahwah,
            const UPtr<MidiTimer>& timer
    )
    {
        return cant::UPtr<MidiController>(new MidiWah(numberVoices, channel, wahwah, timer));
    }

CANTINA_PAN_NAMESPACE_END
