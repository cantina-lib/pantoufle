//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_FLATENVELOPE_HPP
#define CANTINA_FLATENVELOPE_HPP

#pragma once

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class FlatToneEnvelope final : protected ToneEnvelope
    {
    private:
        CANT_EXPLICIT FlatToneEnvelope(size_m numberVoices);
    public:
        void process(MidiNoteInternal& note) override;

        static UPtr<ToneEnvelope> make(size_m numberVoices);

        void flushChange() override;
    };
}
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_FLATENVELOPE_HPP
