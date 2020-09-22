
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
    namespace adsr
    {
        typedef Array<time_d, 4> ArrayLengths;
        typedef Array<type_d , 2> ArrayVelocityRatios;

        typedef Array<type_d, 4> ArraySpeeds;
    }


CANTINA_PAN_NAMESPACE_END

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_ADSR_FORWARD_HPP