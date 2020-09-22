
#ifndef PANTOUFLE_MIDITIMER_HPP
#define PANTOUFLE_MIDITIMER_HPP

#pragma once

#include <cant/time/common/types.hpp>

#include <cant/pan/timer/TimeUpdatable.hpp>
#include <cant/pan/timer/ChangeFlagUpdatable.hpp>

#include <cant/event/Listen.hpp>



// shouldn't have to include this, only forward declaration. Oh well.
// Forward declaration of InternalClock in cant::time
// can't do it inside pan because it will then be in cant::pan::time.
// Reason is that with std::unique_ptr's, the type have to be complete.
// this wouldn't be the case if we were using raw pointer.
// but we won't.
#include <cant/time/InternalClock.hpp>
#include <cant/common/macro.hpp>
/*
CANTINA_TIME_NAMESPACE_BEGIN
    class InternalClock;
CANTINA_TIME_NAMESPACE_END
 */
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiTimer : event::Lecturer
    {
    public:
        /** -- structs -- **/
        class TimeModule : public TimeUpdater
        {
        public:
            /** -- methods -- **/
            CANT_EXPLICIT TimeModule(UPtr<time::InternalClock> internalClock);

            CANT_NODISCARD time_d getCurrentTime() const override;
            CANT_NODISCARD time_d getDeltaTime() const override;


        private:
            /** -- fields -- **/
            UPtr<time::InternalClock> m_internalClock;

            /** -- friends -- **/
            friend class MidiTimer;
        };

        class ChangeFlagModule : public ChangeFlagUpdater
        {

        private:
            /** -- friends -- **/
            friend class MidiTimer;

        };


        /** -- methods -- **/
        MidiTimer();

        void setCustomTimeGetter(time::AbsoluteTimeGetter absoluteTimeGetter);

        void start();
        void stop();
        void update();
        void reset();

        CANT_NODISCARD bool isRunning() const;

        /** -- fields -- **/
        UPtr<TimeModule> timeModule;
        UPtr<ChangeFlagModule> changeFlagModule;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //PANTOUFLE_MIDITIMER_HPP