//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_MIDITIMER_INL
#define CANTINA_TILDE_MIDITIMER_INL

#pragma once

#include <cant/common/macro.hpp>
namespace cant::pan
{
    CANT_INLINE
    std::chrono::time_point<std::chrono::steady_clock> MidiTimer::s_mainTStart = std::chrono::steady_clock::now();

    CANT_INLINE
    MidiTimer::
    MidiTimer() = default;

    CANT_INLINE
    void
    MidiTimer::
    update()
    {
    }

    CANT_INLINE
    time_m
    MidiTimer::
    getCurrentTime() const
    {
        auto t = std::chrono::steady_clock::now();
        std::chrono::duration<time_m> dur = t - s_mainTStart;
        return dur.count() * 1000;
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MIDITIMER_INL
