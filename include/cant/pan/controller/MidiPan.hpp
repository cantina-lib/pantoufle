//
// Created by binabik on 08/08/2020.
//

#ifndef CANTINA_TILDE_MIDIPAN_HPP
#define CANTINA_TILDE_MIDIPAN_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

namespace cant::pan
{
    class MidiPan : MultiMidiController<1>
    {
    private:
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
    private:
        MidiPan(size_m numberVoices, byte_m channel, byte_m controllerId);

        CANT_NODISCARD pan_m getPan() const;
    public:
        void IMPL_process(MidiNoteInternal& note) const override;

        void update(time_m tCurrent) override;

        static UPtr<MidiController> make(size_m numberVoices, byte_m channel, byte_m controllerId);
    };

}

#endif //CANTINA_TILDE_MIDIPAN_HPP
