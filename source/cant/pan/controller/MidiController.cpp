//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/controller/MidiController.hpp>

namespace cant::pan
{

    MidiController::
    MidiController(const size_m numberVoices)
    : MidiProcessorMemory(numberVoices)
    {

    }

    void
    MidiController::
    process(MidiNoteInternal &internal)
    {
        beforeNoteProcess(internal);
        IMPL_process(internal);
        updateVoice(internal);
    }

    void
    MidiController::
    updateVoice(const MidiNoteInternal &note)
    {
        _memory.setVoice(note);
    }


    void
    MidiController::
    receiveControl(const MidiControlInternal& control)
    {
        beforeControlProcess(control);
        IMPL_receiveControl(control);
    }



}

