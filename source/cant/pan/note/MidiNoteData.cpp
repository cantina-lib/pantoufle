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
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    MidiNoteInternalData::
    MidiNoteInternalData(const MidiNoteInputData &input)
    : MidiNoteData<vel_d, tone_d>(input),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    MidiNoteOutputData::
    MidiNoteOutputData()
    : MidiNoteData(),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    MidiNoteOutputData::
    MidiNoteOutputData(const MidiNoteInternalData &internal)
    : MidiNoteData<vel_d, tone_d>(internal.getChannel(), internal.getTone(), internal.getVelocity()),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    Array<vel_d, 2>
    MidiNoteOutputData::
    getVelocityPanned() const
    {
        const vel_d velocity = getVelocity();
        const pan_d pan = getPan();
        const type_d left = (1 - pan) / 2;
        const type_d right = (1 + pan) / 2;
        /* -1 is full left, 1 is full right, 0 is balanced. */
        return { velocity * left, velocity * right };
    }

}
