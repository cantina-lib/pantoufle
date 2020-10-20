//
// Created by binabik on 20/09/2020.
//

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/time/InternalClock.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiTimer::
    MidiTimer()
       : timeModule(std::make_unique<TimeModule>(
               ::cant::time::InternalClock::make(::cant::time::SystemExternalClock::make()))
               ),
       changeFlagModule(std::make_unique<ChangeFlagModule>())

    {

    }

    void
    MidiTimer::
    update()
    {
        timeModule->m_internalClock->update();
        if (this->isRunning())
        {
            timeModule->updateAllSubscribers();
            changeFlagModule->updateAllSubscribers();
        }
    }

    MidiTimer::TimeModule::
    TimeModule(UPtr<time::InternalClock> internalClock)
            : m_internalClock(std::move(internalClock))
    {

    }

    void
    MidiTimer::
    setCustomTimeGetter(time::AbsoluteTimeGetter absoluteTimeGetter)
    {
        this->timeModule->m_internalClock->setCustomTimeGetter(std::move(absoluteTimeGetter));
    }

    time_d
    MidiTimer::TimeModule::
    getCurrentTime() const
    {
        return m_internalClock->getCurrentTime();
    }

    time_d
    MidiTimer::TimeModule::
    getDeltaTime() const
    {
        const time_d t = m_internalClock->getDeltaTime();
        return t;
    }

    void
    MidiTimer::
    start()
    {
        this->timeModule->m_internalClock->start();
    }

    CANT_INLINE
    void
    MidiTimer::
    stop()
    {
        this->timeModule->m_internalClock->stop();
    }


    CANT_INLINE
    void
    MidiTimer::
    reset()
    {
        this->timeModule->m_internalClock->reset();
    }

    CANT_INLINE
    bool
    MidiTimer::
    isRunning() const
    {
        return this->timeModule->m_internalClock->isRunning();
    }





CANTINA_PAN_NAMESPACE_END


