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
        CANT_EXPLICIT FlatToneEnvelope(size_m numberVoices);
    public:
        void processVoice(size_m iVoice, MidiNoteInternal& note) override;

        static UPtr<ToneEnvelope> make(size_m numberVoices);

        void flushChange();
    };
}


#endif //CANTINA_FLATENVELOPE_HPP
