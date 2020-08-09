//
// wah by wah on wah/wahh/waaaahhh
//

#ifndef CANTINA_WAH
#define CANTINA_WAH

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

namespace cant::pan
{
    class MidiWah : MultiMidiController<2>
    {
    private:
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
    private:
        MidiWah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah);

    public:
        void IMPL_process(MidiNoteInternal& note) const override;

        void update(time_m tCurrent) override;

        static UPtr<MidiController> wah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah);
    };

}

#endif //wah!
