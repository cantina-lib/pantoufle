//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/formatting.hpp>
#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

#include <cant/pan/controller/MidiController.hpp>

#include <cant/common/macro.hpp>

namespace cant::pan
{

    /**
     * MidiController should not grant unguarded access
     * to its Processor _memory to child classes.
     * It updates it, but can give a read-only ref.
     **/
     /*
      *
      *
      */
     template <size_m numberBindings>
    class MultiMidiController : protected MidiController
    {
    private:
        byte_m _channel;
        Array<byte_m, numberBindings> _controllerIds;
        Array<MidiControlInternal, numberBindings> _controls;
    private:
        // event functions
        void beforeControlProcess(const MidiControlInternal& control) override = 0;
        void beforeNoteProcess(const MidiNoteInternal& note) override = 0;
        void IMPL_receiveControl(const MidiControlInternal& incomingControl) final
        {
            const byte_m id = incomingControl.getId();
            const auto& controllerIdsBegin = _controllerIds.begin();
            const auto& controllerIdsEnd = _controllerIds.end();
            auto it = std::find(
                    controllerIdsBegin,
                    controllerIdsEnd,
                    id
            );
            if (it != controllerIdsEnd)
            {
                _controls.at(it - controllerIdsBegin)= incomingControl;
            }
            /* not sure about this, I think the controller ought just to ignore the control. */
           // throw PANTOUFLE_EXCEPTION("Control not in bindings of Controller.");
        }
        // to be implemented
        void IMPL_process(MidiNoteInternal& note) const override = 0;

    protected:
        CANT_EXPLICIT MultiMidiController(size_m numberVoices, byte_m channel, Array<byte_m, numberBindings> controllerIds)
        : MidiController(numberVoices),
        _channel(channel),
        _controllerIds(std::move(controllerIds)),
        _controls()
        {

        }


        CANT_NODISCARD const MidiNoteInternal& getMemory(size_m voice) const { return _memory.get(voice); }

        CANT_NODISCARD const MidiControlInternal&
        getControl(const size_m iControl) const
        {
            return _controls.at(iControl);
        }
    public:
        CANT_NODISCARD Stream<byte_m>
        getControllerIds() const override { return Stream<byte_m>(_controllerIds.begin(), _controllerIds.end()); }

        void update(time_m tCurrent) override = 0;

    };
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_MIDICONTROLLER_HPP
