//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_NOTE_FORWARD_HPP
#define CANTINA_TILDE_NOTE_FORWARD_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    template <typename Tone_T, typename Vel_T>
    class MidiNoteData;

    class MidiNoteInputData;
    class MidiNoteInternalData;
    class MidiNoteOutputData;

    template <class Data_T>
    class MidiNote;
    class MidiNoteInput;
    class MidiNoteInternal;
    class MidiNoteOutput;

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_NOTE_FORWARD_HPP
