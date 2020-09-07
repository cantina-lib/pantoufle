//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/controller/MidiController.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

namespace cant::pan
{

    MidiController::
    MidiController(const size_u numberVoices)
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
        m_memory.setVoice(note);
    }


    void
    MidiController::
    receiveControl(const MidiControlInternal& control)
    {
        beforeControlProcess(control);
        IMPL_receiveControl(control);
    }



}

