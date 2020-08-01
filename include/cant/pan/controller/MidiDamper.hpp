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
            CANT_NODISCARD UPtr <ControlledMidiNote> allocateNote(const WPtr <MidiControl> &control) const override;
    private:
        MidiDamper(sizeint numberVoices, byte_m channelId, byte_m controllerId);
    public:
        static UPtr<MidiController> make(sizeint numberVoices, byte_m channelId, byte_m controllerId);
    };
}

#endif //CANTINA_MIDIDAMPER_HPP
