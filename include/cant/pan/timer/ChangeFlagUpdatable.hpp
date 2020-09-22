
#ifndef CANTINA_PAN_FLAGCHANGEUPDATABLE_HPP
#define CANTINA_PAN_FLAGCHANGEUPDATABLE_HPP

#pragma once

#include <cant/event/Listen.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class ChangeFlagUpdatable;

    class ChangeFlagUpdater : public event::LecturerTrait<ChangeFlagUpdatable>
    {
        /*
         * for now, there really isn't anything to add to this
         * (until we add conditions)
         */
    };

    class ChangeFlagUpdatable : public event::ListenerTrait<ChangeFlagUpdater>
    {
    protected:
        /** methods **/
        ChangeFlagUpdatable();

        CANT_NODISCARD bool justChanged() const;

        void raiseChangeFlag();
    private:
        /** -- methods -- **/
        void discardChangeFlag();

        // private inheritance
        void getNotified(event::CPtr<ChangeFlagUpdater> updater) override;


        /** -- fields -- **/
        bool m_flagJustChanged;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_FLAGCHANGEUPDATABLE_HPP