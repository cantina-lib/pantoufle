//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MULTIMIDICONTROLLER_INL
#define CANTINA_TILDE_MULTIMIDICONTROLLER_INL

#pragma once

#include <cant/pan/common/types.hpp>
#include <cant/pan/control/MidiControlData.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    template<size_m numberBindings>
    void
    MultiMidiController<numberBindings>::
    IMPL_receiveControl(const MidiControlInternal &incomingControl)
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

    template<size_m numberBindings>
    MultiMidiController<numberBindings>::
    MultiMidiController(size_m numberVoices, byte_m channel, Array <byte_m, numberBindings> controllerIds)
            : MidiController(numberVoices),
              _channel(channel),
              _controllerIds(std::move(controllerIds)),
              _controls()
    {

    }

    template<size_m numberBindings>
    CANT_NODISCARD CANT_INLINE const MidiNoteInternal
    &MultiMidiController<numberBindings>::
    getMemory(size_m voice) const
    {
        return _memory.getVoice(voice);
    }

    template<size_m numberBindings>
    CANT_NODISCARD CANT_INLINE const MidiControlInternal &
    MultiMidiController<numberBindings>::
    getControl(const size_m iControl) const
    {
        return _controls.at(iControl);
    }

    template<size_m numberBindings>
    CANT_NODISCARD CANT_INLINE
    Stream <byte_m> MultiMidiController<numberBindings>::getControllerIds() const
    {
        return Stream<byte_m>(_controllerIds.begin(), _controllerIds.end());
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MULTIMIDICONTROLLER_INL
