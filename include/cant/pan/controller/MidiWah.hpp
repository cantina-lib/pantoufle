//
// wah by wah on wah/wahh/waaaahhh
//

#ifndef CANTINA_WAH
#define CANTINA_WAH

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiWah : MultiMidiController<2>
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<MidiController> wah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah);

        void update(time_d tCurrent) override;
    private:
        /** -- methods -- **/
        MidiWah(size_u numberVoices, id_u8 channel, Array<id_u8, 2> wahwah);

        // event functions
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
        // private inheritance
        void IMPL_process(MidiNoteInternal& note) const override;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //wah!
