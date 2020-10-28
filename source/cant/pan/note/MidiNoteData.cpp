//
// Created by binabik on 25/07/2020.
//

#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/maths/approx.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

MidiNoteInputData::MidiNoteInputData() = default;

MidiNoteInputData::MidiNoteInputData(id_u8 channel, tone_i8 tone,
                                     vel_i8 velocity)
    : MidiNoteData<tone_i8, vel_i8>(channel, tone, velocity) {}

MidiNoteInputData::MidiNoteInputData(const MidiNoteInputData &other) = default;

MidiNoteInputData &
MidiNoteInputData::operator=(const MidiNoteInputData &other) = default;

MidiNoteInternalData::MidiNoteInternalData()
    : MidiNoteData(), m_pan(static_cast<pan_d>(0)) // balanced pan
{}

void MidiNoteInternalData::setPan(const pan_d pan) {
  m_pan = std::clamp(pan, static_cast<pan_d>(-1), static_cast<pan_d>(1));
}

MidiNoteInternalData::MidiNoteInternalData(const MidiNoteInputData &input)
    : MidiNoteData<tone_d, vel_d>(input),
      m_pan(static_cast<pan_d>(0)) // balanced pan
{}

MidiNoteOutputData::MidiNoteOutputData()
    : MidiNoteData(), m_pan(static_cast<pan_d>(0)) // balanced pan
{}

MidiNoteOutputData::MidiNoteOutputData(const MidiNoteInternalData &internal)
    : MidiNoteData<tone_d, vel_d>(internal.getChannel(), internal.getTone(),
                                  internal.getVelocity()),
      m_pan(static_cast<pan_d>(0)) // balanced pan
{}

CANTINA_PAN_NAMESPACE_END
