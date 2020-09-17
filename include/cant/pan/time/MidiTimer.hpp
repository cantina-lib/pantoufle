//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDITIMER_HPP
#define CANTINA_MIDITIMER_HPP

#pragma once

#include <functional>

#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiTimer
    {
    public:
        /** -- internal structs -- **/
        typedef std::function<time_d()> CurrentTimeGetter;
        /** -- methods -- **/
        MidiTimer();
        virtual ~MidiTimer();

        virtual void update() = 0;
        void start();
        void stop();

        CANT_NODISCARD bool isStarted() const;

        CANT_NODISCARD type_d getCurrentTime() const;
        CANT_NODISCARD type_d getDeltaTime() const;

    private:
        /** -- methods -- **/
        CANT_NODISCARD virtual time_d getCurrentTimeInternal() const = 0;
        CANT_NODISCARD virtual time_d getDeltaTimeInternal() const = 0;

        virtual void reset() = 0;

        /** -- fields -- **/
        bool m_isStarted;
        // constants
        static CANT_CONSTEXPR type_d c_inMilliseconds = 1000;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/time/MidiTimer.inl>

#endif //CANTINA_MIDITIMER_HPP
