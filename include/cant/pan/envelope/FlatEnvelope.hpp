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
    public:
        /** -- methods -- **/
        // factory method
        static UPtr<ToneEnvelope> make(size_m numberVoices);

        void process(MidiNoteInternal& note) override;

        void flushChange() override;
    private:
        /** -- methods -- **/
        CANT_EXPLICIT FlatToneEnvelope(size_m numberVoices);
    };
}
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_FLATENVELOPE_HPP
