//
// Created by binabik on 05/06/2020.
//

#ifndef CANTINA_MIDIDAMPER_HPP
#define CANTINA_MIDIDAMPER_HPP

#pragma once

#include <cant/pan/controller/MidiController.hpp>


namespace cant::pan
{
    class MidiDamper final : public MidiController
    {
    private:
        bool _flagShouldHold;
    private:
        void beforeControlChange(const MidiControlInternal& incoming) override;
        void beforeNoteChange(size_m iVoice, const MidiNoteInternal& incoming) override;
    private:
        MidiDamper(size_m numberVoices, byte_m channelId, byte_m controllerId);

        CANT_NODISCARD bool isOn() const;
        CANT_NODISCARD static bool isOn(const MidiControlInternal& control);
    public:
        void IMPL_processVoice(size_m iVoice, MidiNoteInternal& note) const override;

        void update(time_m tCurrent) override;

        static UPtr<MidiController> make(size_m numberVoices, byte_m channelId, byte_m controllerId);
    };
}

#endif //CANTINA_MIDIDAMPER_HPP
