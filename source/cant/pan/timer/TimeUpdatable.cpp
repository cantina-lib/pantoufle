//
// Created by binabik on 19/09/2020.
//

#include <cant/pan/timer/TimeUpdatable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    void
    DeltaTimeUpdatable::
    getNotified(event::CPtr<TimeUpdater> updater)
    {
        this->updateDelta(updater->getDeltaTime());
    }

    void
    CurrentTimeUpdatable::
    getNotified(event::CPtr<TimeUpdater> updater)
    {
        this->updateCurrent(updater->getCurrentTime());
    }


CANTINA_PAN_NAMESPACE_END


