//
// Created by binabik on 24/08/2020.
//

#ifndef CANTINA_TILDE_MULTIMIDICONTROLLER_INL
#define CANTINA_TILDE_MULTIMIDICONTROLLER_INL

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

    template<size_u numberBindings>
    void
    MultiMidiController<numberBindings>::
    IMPL_receiveControl(const MidiControlInternal &incomingControl)
    {
        const id_u8 id = incomingControl.getId();
        const auto& controllerIdsBegin = m_controllerIds.begin();
        const auto& controllerIdsEnd = m_controllerIds.end();
        auto it = std::find(
                controllerIdsBegin,
                controllerIdsEnd,
                id
        );
        if (it != controllerIdsEnd)
        {
            m_controls.at(it - controllerIdsBegin)= incomingControl;
        }
        /* not sure about this, I think the controller ought just to ignore the control. */
        // throw PANTOUFLE_EXCEPTION("Control not in bindings of Controller.");
    }

    template<size_u numberBindings>
    MultiMidiController<numberBindings>::
    MultiMidiController(size_u numberVoices, id_u8 channel, Array <id_u8, numberBindings> controllerIds)
            : MidiController(numberVoices),
              m_channel(channel),
              m_controllerIds(std::move(controllerIds)),
              m_controls()
    {

    }

    template<size_u numberBindings>
    CANT_NODISCARD CANT_INLINE
    const MidiNoteInternal&
    MultiMidiController<numberBindings>::
    getMemory(size_u voice) const
    {
        return m_memory.getVoice(voice);
    }

    template<size_u numberBindings>
    CANT_NODISCARD CANT_INLINE
    const MidiControlInternal&
    MultiMidiController<numberBindings>::
    getControl(const size_u iControl) const
    {
        return m_controls.at(iControl);
    }

    template<size_u numberBindings>
    CANT_NODISCARD CANT_INLINE
    Stream<id_u8>
    MultiMidiController<numberBindings>::getControllerIds() const
    {
        return Stream<id_u8>(m_controllerIds.begin(), m_controllerIds.end());
    }
}

#include <cant/common/undef_macro.hpp>
#endif //CANTINA_TILDE_MULTIMIDICONTROLLER_INL
