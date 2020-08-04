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
        beforeNoteProcess(iVoice, internal);
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
        beforeControlProcess(control);
        _control = control;
    }



}

