//
// Created by binabik on 17/09/2020.
//

#ifndef CANTINA_TILDE_MIDITIMER_INL
#define CANTINA_TILDE_MIDITIMER_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    MidiTimer::
    MidiTimer()
            : m_isStarted(false)
    {}

    CANT_INLINE
    MidiTimer::
    ~MidiTimer() = default;

    CANT_INLINE
    type_d
    MidiTimer::
    getCurrentTime() const
    {
        return c_inMilliseconds * getCurrentTimeInternal();
    }

    CANT_INLINE
    type_d
    MidiTimer::
    getDeltaTime() const
    {
        return c_inMilliseconds * getDeltaTimeInternal();
    }

    CANT_INLINE
    void
    MidiTimer::
    start()
    {
        if (!isStarted())
        {
            reset();
            m_isStarted = true;
        }
    }

    CANT_INLINE
    void
    MidiTimer::
    stop()
    {
        m_isStarted = false;
    }

    CANT_INLINE
    bool
    MidiTimer::
    isStarted() const
    {
        return m_isStarted;
    }

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_MIDITIMER_INL
