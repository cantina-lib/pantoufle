//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/control/MidiControl.hpp>

namespace cant::pan
{
    ShPtr <MidiControl>
    MidiControl::
    makeShared()
    {
        return ShPtr<MidiControl>(new MidiControl());
    }

    void
    MidiControl::
    set(WPtr<MidiControl> &dest, const ShPtr<MidiControl> &src)
    {
        if (!isControlSet(src))
        {
            throw PANTOUFLE_EXCEPTION("Control not set.");
        }
        /* copy ref to content */
        dest = src;
    }

    void
    MidiControl::
    reset(WPtr<MidiControl> &dest)
    {
        dest.reset();
    }

    bool
    MidiControl::
    isControlSet(const MidiControl* control)
    {
        return static_cast<bool>(control);
    }

    bool
    MidiControl::
    isControlSet(const ShPtr<MidiControl> &control)
    {
        return isControlSet(control.get());
    }

    MidiControl::
    MidiControl(const MidiControlInput& input)
    : _input(input)
    {

    }

    void
    MidiControl::
    update(ShPtr<MidiControl>& control, const MidiControlInput& input)
    {
        if (!isControlSet(control))
        {
            control.reset(new MidiControl(input));
        }
        else
        {
            control->_input = input;
        }

    }

    byte_m
    MidiControl::
    getValue() const
    {
       return _input.getValue();
    }

    byte_m
    MidiControl::
    getControllerId() const
    {
        return _input.getControllerId();
    }

    std::ostream&
    operator<<(std::ostream& out, const MidiControl* control)
    {
        out << "[midicontrol]";
        if(!MidiControl::isControlSet(control))
        {
            out << "[NOTSET]";
            return out;
        }
        out << control->_input;
        return out;
    }

    std::ostream&
    operator<<(std::ostream& out, const ShPtr<MidiControl>& control)
    {
        return out << control.get();
    }
}
