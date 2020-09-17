//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_CONTROL_FORWARD_HPP
#define CANTINA_TILDE_CONTROL_FORWARD_HPP

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiControlData;

    typedef MidiControlData MidiControlInputData;
    typedef MidiControlInputData MidiControlInput;

    typedef MidiControlInput MidiControlInternal;

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_CONTROL_FORWARD_HPP
