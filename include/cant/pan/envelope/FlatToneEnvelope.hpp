//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_PAN_FLATTONEENVELOPE_HPP
#define CANTINA_PAN_FLATTONEENVELOPE_HPP

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
        static UPtr<ToneEnvelope> make();

        void process(MidiNoteInternal& note) override;

    private:
        /** -- methods -- **/
        //private inheritance
        void updateDelta(time_d tDelta) override;

    };
}
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_PAN_FLATTONEENVELOPE_HPP
