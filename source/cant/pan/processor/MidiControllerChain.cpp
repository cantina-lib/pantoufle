//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/processor/MidiControllerChain.hpp>

namespace cant::pan
{
    MidiControllerChain::
    MidiControllerChain(size_m numberVoices)
    : m_numberVoices(numberVoices),
      m_controllers(),
      m_controls()
    {
        m_controllers.reserve(c_controllerStartingSize);
    }

    void
    MidiControllerChain::
    receiveControl(const MidiControlInternal& control)
    {
        const byte_m controllerId = control.getId();
        if (m_controls.find(controllerId) == m_controls.end())
        {
            return;
        }
        m_controls.at(controllerId) = control;
        for (auto& controller : m_controllers)
        {
            controller->receiveControl(control);
        }
    }

    void
    MidiControllerChain::
    allocateControls(const Stream<byte_m>& controllerIds)
    {
        for (const auto& controllerId : controllerIds)
        {
            /*
             * In a map, attempting to inserting an already-present key
             * will not actually insert it.
             */
            m_controls.insert(std::pair<byte_m, MidiControlInternal>(controllerId, MidiControlInternal()));
        }
    }

    void
    MidiControllerChain::
    process(MidiNoteInternal &in)
    {
        for(auto& controller: m_controllers)
        {
            controller->process(in);
        }
    }

    void
    MidiControllerChain::
    update(const time_m tCurrent)
    {
        // will notes need updating in processors?
        // updateMidiNoteStream(_memory, tCurrent);

        /*
         * I mean, we could have a mechanic like,
         * a control's value can decrease as time passes.
         * Wait, there *are* controller like that..
         */
        for (auto& controller : m_controllers)
        {
            controller->update(tCurrent);
        }
    }

    void
    MidiControllerChain::
    addController(UPtr<MidiController> controller)
    {
        allocateControls(controller->getControllerIds());
        m_controllers.push_back(std::move(controller));
    }
}
