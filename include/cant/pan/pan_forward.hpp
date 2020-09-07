//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_PAN_FORWARD_HPP
#define CANTINA_TILDE_PAN_FORWARD_HPP

#pragma once

#include <cant/pan/layer/MidiNoteLayer.hpp>

namespace cant::pan
{
    class MidiControllerChain;
    class MidiEnvelopePair;
    class MidiTimer;

    template <typename T>
    class MidiNoteLayer;
    class MidiNoteInputPoly;

    class MidiController;
    class MidiControlData;
    template <typename T, typename V>
    class MidiNoteData;
    class MidiNoteOutput;
}

#endif //CANTINA_TILDE_PAN_FORWARD_HPP
