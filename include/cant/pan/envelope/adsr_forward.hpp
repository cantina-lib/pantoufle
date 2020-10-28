
#ifndef CANTINA_PAN_ADSR_FORWARD_HPP
#define CANTINA_PAN_ADSR_FORWARD_HPP

#pragma once

#include <cant/common/macro.hpp>

CANTINA_PAN_NAMESPACE_BEGIN

class ADSREnvelope;
class MidiNoteInternal;

class ADSREnvelope;
class ADSRState;

// Array
namespace adsr {
/*
 * 0: attack time
 * 1: sustain time, can be infinite -> reserved value (negative)
 * 2: decay time
 * 3: release time
 */

typedef Array<time_d, 4> ArrayLengths;
/*
 * 0: attack peak velocity
 * 1: sustain velocity
 */
typedef Array<type_d, 2> ArrayVelocityRatios;
/*
 * inferred from the other two
 * The lengths won't actually be respected, they are only targets,
 * and the velocity ratios will change at the specified rates.
 * positive!!!!
 */
typedef Array<type_d, 4> ArraySpeeds;
} // namespace adsr

CANTINA_PAN_NAMESPACE_END

#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_ADSR_FORWARD_HPP