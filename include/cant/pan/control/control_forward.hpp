//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_CONTROL_FORWARD_HPP
#define CANTINA_TILDE_CONTROL_FORWARD_HPP

#pragma once

namespace cant::pan
{
    class MidiControlData;

    typedef MidiControlData MidiControlInputData;
    typedef MidiControlInputData MidiControlInput;

    typedef MidiControlInput MidiControlInternal;
    /* has had no meaning so far */
    // using MidiControlOutputData = MidiControlData;
}

#endif //CANTINA_TILDE_CONTROL_FORWARD_HPP
