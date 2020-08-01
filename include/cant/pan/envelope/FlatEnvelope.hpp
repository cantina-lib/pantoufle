//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_FLATENVELOPE_HPP
#define CANTINA_FLATENVELOPE_HPP

#pragma once

#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::pan
{
    class FlatToneEnvelope final : protected ToneEnvelope
    {
    private:
        FlatToneEnvelope() = default;
    public:
        void apply(time_m tCurrent, MidiNoteInternal& note) const override;

        static UPtr<ToneEnvelope> make();
    };
}


#endif //CANTINA_FLATENVELOPE_HPP
