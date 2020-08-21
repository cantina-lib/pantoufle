//
// Created by binabik on 05/06/2020.
//

#ifndef CANTINA_MIDIDAMPER_HPP
#define CANTINA_MIDIDAMPER_HPP

#pragma once

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiDamper final : public MultiMidiController<1>
    {
    private:
        /*
         * Can't be bool, since Stream are actually std::vector, and c++ does summat
         * funky with std::vector<bool> template specialisation.
         */
        Stream<byte_m> _shouldHoldNotes;
        /*
         * It's not necessary to use this additional vector,
         * we could just use getMemory(iVoice).isPlaying().
         * However, I think that accessing the memory of the last processed notes
         * in the function in charge of processing is, in concept, a bad idea.
         * I'd rather save the values I'm interested in in the dedicated
         * function beforeNoteProcess(), where I get insurance
         * that this code will be executed *before* any new processing is done.
         */
        Stream<byte_m> _isMemoryPlaying;
    private:
        void beforeControlProcess(const MidiControlInternal& incomingControl) override;
        void beforeNoteProcess(const MidiNoteInternal& incomingNote) override;
    private:
        MidiDamper(size_m numberVoices, byte_m channel, byte_m controllerId);

        CANT_NODISCARD bool isOn() const;
        CANT_NODISCARD static bool isOn(const MidiControlInternal& control);
    public:
        void IMPL_process(MidiNoteInternal& note) const override;

        void update(time_m tCurrent) override;

        static UPtr<MidiController> make(size_m numberVoices, byte_m channel, byte_m controllerId);
    };
}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_MIDIDAMPER_HPP
