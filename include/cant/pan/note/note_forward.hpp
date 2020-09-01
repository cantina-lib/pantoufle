//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_NOTE_FORWARD_HPP
#define CANTINA_TILDE_NOTE_FORWARD_HPP

#pragma once

#include <cant/pan/common/types.hpp>

namespace cant::pan
{
    template <typename Tone_T, typename Vel_T>
    class MidiNoteData;

    using MidiNoteInputData = MidiNoteData<tone_mint, vel_mint>;
    class MidiNoteInternalData;
    class MidiNoteOutputData;

    template <class Data_T>
    class MidiNote;
    class MidiNoteInput;
    class MidiNoteInternal;
    class MidiNoteOutput;
}

#endif //CANTINA_TILDE_NOTE_FORWARD_HPP
