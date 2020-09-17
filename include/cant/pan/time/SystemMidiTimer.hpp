//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_SYSTEMMIDITIMER_HPP
#define CANTINA_SYSTEMMIDITIMER_HPP

#pragma once

#include <chrono>

#include <cant/pan/common/types.hpp>

#include <cant/pan/time/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class SystemMidiTimer : public MidiTimer
    {
    public:
        /** -- internal structs -- **/
        typedef std::chrono::steady_clock Clock;
        /** -- methods -- **/
        SystemMidiTimer();

        void update() override;

    private:
        /** -- methods -- **/
        // private inheritance
        CANT_NODISCARD time_d getCurrentTimeInternal() const override;
        CANT_NODISCARD time_d getDeltaTimeInternal() const override;

        void reset() override;

        /** -- fields -- **/
        std::chrono::time_point<Clock> m_tStart;
        std::chrono::time_point<Clock> m_tCurrent;
        std::chrono::time_point<Clock> m_tLast;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/time/SystemMidiTimer.inl>

#endif // CANTINA_SYSTEMMIDITIMER_HPP
