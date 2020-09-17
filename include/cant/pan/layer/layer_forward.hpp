//
// Created by binabik on 17/09/2020.
//

#ifndef CANTINA_TILDE_LAYER_FORWARD_HPP
#define CANTINA_TILDE_LAYER_FORWARD_HPP

#pragma once

#include <cant/pan/note/note_forward.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    template <class Note_T>
    class MidiNoteLayer;
    class MidiNoteInputLayer;
    template <class Note_T, class PreviousLayerNote_T>
    class MidiNoteInternalOutputLayer;

    typedef MidiNoteInternalOutputLayer<MidiNoteInternal, MidiNoteInput> MidiNoteInternalLayer;
    typedef MidiNoteInternalOutputLayer<MidiNoteOutput, MidiNoteInternal> MidiNoteOutputLayer;

    class MidiNoteInputPoly;

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_LAYER_FORWARD_HPP
