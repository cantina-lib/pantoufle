//
// Created by binabik on 17/09/2020.
//

#ifndef CANTINA_TILDE_CUSTOMMIDITIMER_HPP
#define CANTINA_TILDE_CUSTOMMIDITIMER_HPP

#pragma once

#include <functional>

#include <cant/pan/common/types.hpp>

#include <cant/pan/time/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class CustomMidiTimer : public MidiTimer
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT CustomMidiTimer(CurrentTimeGetter currentTimeGetter);

        void update() override;

    private:
        /** -- methods -- **/
        // private inheritance
        CANT_NODISCARD time_d getCurrentTimeInternal() const override;
        CANT_NODISCARD time_d getDeltaTimeInternal() const override;

        void reset() override;

        /** -- fields -- **/
        CurrentTimeGetter m_currentTimeGetter;
        time_d m_tCurrent;
        time_d m_tStart;
        time_d m_tLast;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/time/CustomMidiTimer.inl>

#endif //CANTINA_TILDE_CUSTOMMIDITIMER_HPP
