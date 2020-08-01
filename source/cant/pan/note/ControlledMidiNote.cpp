//
// Created by binabik on 04/06/2020.
//

#include <cant/pan/note/ControlledMidiNote.hpp>

#include <sstream>

namespace cant::pan
{

    ControlledMidiNote::
    ControlledMidiNote(WPtr<MidiControl> control)
    :_control(std::move(control))
    {

    }

    ControlledMidiNote::
    ControlledMidiNote(const ControlledMidiNote& ctrlNote)
    : DecoratedMidiNote(ctrlNote), _control(ctrlNote._control)
    {
        if(!ctrlNote.isSet())
        {
            throw PANTOUFLE_EXCEPTION("Note should be set before being copied");
        }
    }

    const WPtr<MidiControl>&
    ControlledMidiNote::
    getControl() const
    {
        if (!isControlSet())
        {
            throw PANTOUFLE_EXCEPTION("Control not set");
        }
        return _control;
    }

    bool
    ControlledMidiNote::
    isControlSet() const
    {
        const auto& locked = _control.lock();
        if (!locked)
        {
            return false;
        }
        return MidiControl::isControlSet(locked);
    }

    bool
    ControlledMidiNote::
    isSet() const
    {
        return isControlSet() && DecoratedMidiNote::isSet();
    }

    bool
    ControlledMidiNote::
    isExtensible() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Controlled note not set.");
        }
        return isBaseExtensible();
    }


    std::string
    ControlledMidiNote::
    print() const
    {
        std::stringstream stream;
        stream << "[controlled] { ";
        const auto& control = _control.lock();
        if (control)
        {
            stream << control;
        }
        else
        {
            stream << "[EXPIRED]";
        }
        stream << DecoratedMidiNote::print() << " }";
        return stream.str();
    }

}
