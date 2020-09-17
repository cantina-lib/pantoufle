//
// Created by binabik on 01/09/2020.
//

#ifndef CANTINA_TILDE_CUSTOMMIDITIMER_INL
#define CANTINA_TILDE_CUSTOMMIDITIMER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    CustomMidiTimer::
    CustomMidiTimer(CurrentTimeGetter currentTimeGetter)
    : m_currentTimeGetter(std::move(currentTimeGetter)),
    m_tCurrent(),
    m_tStart(),
    m_tLast()
    {}

    CANT_INLINE
    void
    CustomMidiTimer::
    update()
    {
        if (isStarted())
        {
            m_tLast = m_tCurrent;
            m_tCurrent = m_currentTimeGetter();
        }
    }

    CANT_INLINE
    void
    CustomMidiTimer::
    reset()
    {
        m_tStart = m_tCurrent = m_tLast = m_currentTimeGetter();
    }

    CANT_INLINE
    time_d
    CustomMidiTimer::
    getCurrentTimeInternal() const
    {
        return m_tCurrent;
    }

    CANT_INLINE
    time_d
    CustomMidiTimer::
    getDeltaTimeInternal() const
    {
        return m_tCurrent - m_tLast;
    }

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_CUSTOMMIDITIMER_INL
