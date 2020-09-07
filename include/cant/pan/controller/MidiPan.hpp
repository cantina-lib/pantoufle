//
// Created by binabik on 08/08/2020.
//

#ifndef CANTINA_TILDE_MIDIPAN_HPP
#define CANTINA_TILDE_MIDIPAN_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>


#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiPan : MultiMidiController<1>
    {
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<MidiController> make(size_u numberVoices, id_u8 channel, id_u8 controllerId);

        void update(time_d tCurrent) override;
    private:
        /** -- methods -- **/
        MidiPan(size_u numberVoices, id_u8 channel, id_u8 controllerId);

        CANT_NODISCARD pan_d getPan() const;

        // event functions
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
        // private inheritance
        void IMPL_process(MidiNoteInternal& note) const override;
    };

}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDIPAN_HPP
