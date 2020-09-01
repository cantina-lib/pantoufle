//
// wah by wah on wah/wahh/waaaahhh
//

#ifndef CANTINA_WAH
#define CANTINA_WAH

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiWah : MultiMidiController<2>
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<MidiController> wah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah);

        void update(time_m tCurrent) override;
    private:
        /** -- methods -- **/
        MidiWah(size_m numberVoices, byte_m channel, Array<byte_m, 2> wahwah);

        // event functions
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
        // private inheritance
        void IMPL_process(MidiNoteInternal& note) const override;
    };

}
#include <cant/common/undef_macro.hpp>
#endif //wah!
