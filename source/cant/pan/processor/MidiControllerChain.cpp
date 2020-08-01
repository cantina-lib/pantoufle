//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/processor/MidiControllerChain.hpp>

namespace cant::pan
{
    MidiControllerChain::
    MidiControllerChain(const size_m numberVoices)
    : MidiProcessorMemory(numberVoices), _controllers()
    {

    }

    void
    MidiControllerChain::
    processControl(const MidiControlInput& input)
    {
        auto it = _controllers.find(input.getControllerId());
        if (it == _controllers.end() || !it->second)
        {
            /* no input control, skipping this controller. */
            return;
        }
        PANTOUFLE_TRY_RETHROW({
             it->second->receiveControl(input);
        })

    }

    void
    MidiControllerChain::
    processVoice(const size_m iVoice, MidiNoteInternal &in)
    {
        for(auto& [id, controller] : _controllers)
        {
            controller->processVoice(iVoice, in);
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
         * whatever.
         */
    }

void
MidiControllerChain::
setController(UPtr<MidiController> controller)
    {
        const byte_m id = controller->getControllerId();
        auto entry = std::pair<byte_m, UPtr<MidiController>>(id, std::move(controller));
        auto it = _controllers.find(id);
        /* is controller not yet set? */
        if (it == _controllers.cend())
        {
            _controllers.insert(std::move(entry));
        }
        else
        {
            _controllers.at(id) = std::move(entry.second);
        }
    }
}
