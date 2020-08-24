//
// Created by binabik on 25/07/2020.
//

#include <cant/pan/note/MidiNoteData.hpp>

#include <algorithm>

namespace cant::pan
{
    MidiNoteInternalData::
    MidiNoteInternalData()
    : MidiNoteData(),
    _pan(static_cast<pan_m>(0)) // balanced pan
    {

    }

    MidiNoteInternalData::
    MidiNoteInternalData(const MidiNoteInputData &input)
    : MidiNoteData<vel_m, tone_m>(input),
    _pan(static_cast<pan_m>(0)) // balanced pan
    {

    }

    MidiNoteOutputData::
    MidiNoteOutputData()
    : MidiNoteData(),
      _pan(static_cast<pan_m>(0)) // balanced pan
    {

    }

    MidiNoteOutputData::
    MidiNoteOutputData(const MidiNoteInternalData &internal)
    : MidiNoteData<vel_m, tone_m>(internal.getChannel(), internal.getTone(), internal.getVelocity()),
      _pan(static_cast<pan_m>(0)) // balanced pan
    {

    }

    Array<vel_m, 2>
    MidiNoteOutputData::
    getVelocityPanned() const
    {
        const vel_m velocity = getVelocity();
        const pan_m pan = getPan();
        const float_m left = (1 - pan) / 2;
        const float_m right = (1 + pan) / 2;
        /* -1 is full left, 1 is full right, 0 is balanced. */
        return { velocity * left, velocity * right };
    }

}
