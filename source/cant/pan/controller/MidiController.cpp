//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/controller/MidiController.hpp>


namespace cant::pan
{
    MidiController::
    MidiController(const size_m numberVoices, const byte_m channel, const byte_m id)
    : MidiProcessorMemory(numberVoices),
    _channel(channel),
    _controllerId(id),
    _control()
    {

    }

    void
    MidiController::
    processVoice(const size_m iVoice, MidiNoteInternal &internal)
    {
        beforeNoteChange(iVoice, internal);
        IMPL_processVoice(iVoice, internal);
        updateVoice(iVoice, internal);
    }

    void
    MidiController::
    updateVoice(const size_m iVoice, const MidiNoteInternal &note)
    {
        _memory.at(iVoice) = note;
    }

    bool
    MidiController::
    isControllerSet(const MidiController* controller)
    {
        return static_cast<bool>(controller);
    }

    bool
    MidiController::
    isControllerSet(const UPtr<MidiController>& controller)
    {
        return isControllerSet(controller.get());
    }


    void
    MidiController::
    receiveControl(const MidiControlInternal& control)
    {
        _control = control;
        beforeControlChange(control);
    }


    std::ostream&
    operator<<(std::ostream& out, const MidiController* controller)
    {
        out << "[midicontroller]";
        if (!MidiController::isControllerSet(controller))
        {
            return out << "!NOTSET";
        }
        out << '#' << (int) controller->getControllerId() << " : ";
        out << controller->getControl();
        return out;
    }

    std::ostream&
    operator<<(std::ostream& out, const UPtr<MidiController>& controller)
    {
        return out << controller.get();
    }

}

