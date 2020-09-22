//
// Created by binabik on 20/09/2020.
//

#include <cant/pan/timer/ChangeFlagUpdatable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    ChangeFlagUpdatable::
    ChangeFlagUpdatable()
            : m_flagJustChanged(false)
    { }

    bool
    ChangeFlagUpdatable::
    justChanged() const
    {
        return m_flagJustChanged;
    }

    void
    ChangeFlagUpdatable::
    raiseChangeFlag()
    {
        m_flagJustChanged = true;
    }

    void
    ChangeFlagUpdatable::
    discardChangeFlag()
    {
        m_flagJustChanged = false;
    }

    void
    ChangeFlagUpdatable::
    getNotified(CANT_MAYBEUNUSED event::CPtr<ChangeFlagUpdater> updater)
    {
        /*
         * Hey, we can add a time-out or conditions this way!
         * todo!
         */
        discardChangeFlag();
    }


CANTINA_PAN_NAMESPACE_END

