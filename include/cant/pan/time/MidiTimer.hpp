//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_TIME_HPP
#define CANTINA_TIME_HPP

#pragma once

#include <chrono>

#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    class MidiTimer
    {
    public:
        /** -- methods -- **/
       MidiTimer();

       void update();

       CANT_NODISCARD time_m getCurrentTime() const;
    private:
        /** -- fields -- **/
        static std::chrono::time_point<std::chrono::steady_clock> s_mainTStart;
    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TIME_HPP
