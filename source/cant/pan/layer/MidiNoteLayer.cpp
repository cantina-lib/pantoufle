//
// Created by binabik on 30/08/2020.
//

#include <cant/pan/layer/MidiNoteLayer.hpp>

#include <cant/pan/note/MidiNote.hpp>

namespace cant::pan
{
    MidiNoteInputLayer::
    MidiNoteInputLayer(size_m numberVoices)
        : MidiNoteLayer<MidiNoteInput>(numberVoices)
    {
    }

}

