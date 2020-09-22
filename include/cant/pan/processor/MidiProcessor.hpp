//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDIPROCESSOR_HPP
#define CANTINA_MIDIPROCESSOR_HPP

#pragma once


#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiNoteInternal;

    class MidiProcessor
    {
    public:
        /** -- methods -- **/
        virtual ~MidiProcessor() = default;

        virtual void process(MidiNoteInternal& in) = 0;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>


#endif //CANTINA_MIDIPROCESSOR_HPP
