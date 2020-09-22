
#ifndef CANTINA_PAN_TIMEUPDATABLE_HPP
#define CANTINA_PAN_TIMEUPDATABLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/event/Listen.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class TimeUpdatable;

    typedef event::LecturerTrait<TimeUpdatable> TimeUpdaterTrait;


    class TimeUpdater : public TimeUpdaterTrait
    {
    public:
        /** -- methods -- **/
        CANT_NODISCARD virtual time_d getCurrentTime() const = 0;
        CANT_NODISCARD virtual time_d getDeltaTime() const = 0;
    };

    typedef event::ListenerTrait<TimeUpdater> TimeUpdatableTrait;


    class TimeUpdatable : public TimeUpdatableTrait
    {
    private:
        /** -- methods -- **/
        // private inheritance
        void getNotified(event::CPtr<TimeUpdater> updater) override = 0;
    };

    class DeltaTimeUpdatable : public TimeUpdatable
    {
    private:
        /** -- methods -- **/
        virtual void updateDelta(time_d tDelta) = 0;

        // private inheritance
        void getNotified(event::CPtr<TimeUpdater> updater) override;
    };

    class CurrentTimeUpdatable : public TimeUpdatable
    {
    private:
        /** -- methods -- **/
        virtual void updateCurrent(time_d tCurrent) = 0;

        // private inheritance
        void getNotified(event::CPtr<TimeUpdater> updater) override;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_TIMEUPDATABLE_HPP