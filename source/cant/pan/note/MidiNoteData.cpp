//
// Created by binabik on 25/07/2020.
//

#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/maths/maths.hpp>

namespace cant::pan
{
    MidiNoteInputData::
    MidiNoteInputData() = default;

    MidiNoteInputData::
    MidiNoteInputData(id_u8 channel, tone_i8 tone, vel_i8 velocity)
    : MidiNoteData<tone_i8, vel_i8>(channel, tone, velocity)
    {}

    MidiNoteInputData::
    MidiNoteInputData(const MidiNoteInputData& other) = default;

    MidiNoteInputData&
    MidiNoteInputData::
    operator=(const MidiNoteInputData &other) = default;

    MidiNoteInternalData::
    MidiNoteInternalData()
    : MidiNoteData(),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {}

    MidiNoteInternalData::
    MidiNoteInternalData(const MidiNoteInputData &input)
    : MidiNoteData<tone_d, vel_d>(input),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {}

    MidiNoteOutputData::
    MidiNoteOutputData()
    : MidiNoteData(),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    MidiNoteOutputData::
    MidiNoteOutputData(const MidiNoteInternalData &internal)
    : MidiNoteData<tone_d, vel_d>(internal.getChannel(), internal.getTone(), internal.getVelocity()),
      m_pan(static_cast<pan_d>(0)) // balanced pan
    {

    }

    ArrayPan
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
