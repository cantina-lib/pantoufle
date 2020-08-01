//
// Created by binabik on 04/06/2020.
//

#ifndef CANTINA_CONTROLLEDMIDINOTE_HPP
#define CANTINA_CONTROLLEDMIDINOTE_HPP

#pragma once

#include <cant/pan/note/DecoratedMidiNote.hpp>

#include <cant/pan/control/MidiControl.hpp>

namespace cant::pan
{
    class MidiController;
    class ControlledMidiNote : public DecoratedMidiNote
    {
        friend MidiController;
    private:
        WPtr<MidiControl> _control;
    private: // unusable here, used by base class
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override = 0;
        CANT_NODISCARD bool justChanged() const override = 0;

        virtual void onControlChange() = 0;
    protected:
        CANT_NODISCARD bool isExtensible() const override;

        CANT_NODISCARD const WPtr<MidiControl>& getControl() const;
        /* todo: hey! it should be private! */
        CANT_NODISCARD bool isControlSet() const;
        CANT_NODISCARD bool isSet() const final;

        CANT_NODISCARD std::string print() const override;
        /*
         * control will be updated by the controller
         * we store a ref to the control so no need to do it here
         */
        // void update(time_m tCurrent) override;

        CANT_EXPLICIT ControlledMidiNote(WPtr<MidiControl> control);
        ControlledMidiNote(const ControlledMidiNote&);
    public:

        CANT_NODISCARD bool isPlaying() const override = 0;

        CANT_NODISCARD tone_m getTone() const override = 0;
        CANT_NODISCARD vel_m getVelocity() const override = 0;

    };
}

#endif //CANTINA_CONTROLLEDMIDINOTE_HPP
