//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_SYSTEMMIDITIMER_INL
#define CANTINA_TILDE_SYSTEMMIDITIMER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    SystemMidiTimer::
    SystemMidiTimer()
        : m_tStart(),
        m_tCurrent(),
        m_tLast()
    {}

    CANT_INLINE
    void
    SystemMidiTimer::
    update()
    {
        if (isStarted())
        {
            m_tLast = m_tCurrent;
            m_tCurrent = Clock::now();
        }
    }

    CANT_INLINE
    void
    SystemMidiTimer::
    reset()
    {
        m_tStart = m_tCurrent = m_tLast = Clock::now();
    }

    CANT_INLINE
    time_d
    SystemMidiTimer::
    getCurrentTimeInternal() const
    {
        return static_cast<time_d>((m_tCurrent - m_tStart).count());
    }

    CANT_INLINE
    time_d
    SystemMidiTimer::
    getDeltaTimeInternal() const
    {
        return static_cast<time_d>((m_tCurrent - m_tLast).count());
    }

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_SYSTEMMIDITIMER_INL
