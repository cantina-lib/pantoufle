//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/processor/MidiControllerChain.hpp>

#include <cant/pan/note/LazyMidiNote.hpp>

namespace cant::midi
{
    MidiControllerChain::
    MidiControllerChain(const sizeint numberVoices)
    : MidiProcessorMemory(numberVoices), _controllers()
    {
        allocatedProcessed();
    }

    void
    MidiControllerChain::
    allocatedProcessed()
    {
        for (auto& note : _processed)
        {
            note = LazyMidiNote::make();
        }
    }


    void
    MidiControllerChain::
    processControl(const MidiControlInput& input, const UStream<MidiNote>& inStream)
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
    update(const time_m tCurrent)
    {
        MidiProcessorMemory::update(tCurrent);
        for (auto& controller : _controllers)
        {
            controller.second->update(tCurrent);
        }
    }

    void
    MidiControllerChain::
    processVoice(sizeint iVoice, const UPtr<MidiNote> &in)
    {
        if (!MidiNote::isNoteSet(in))
        {
            throw PANTOUFLE_EXCEPTION("Received note not set.");
        }
        auto& lastProcessedNote = _processed.at(iVoice);
        const bool shouldChainProcess = !_controllers.empty();
        if (shouldChainProcess)
        {
            auto it = _controllers.begin();
            /* */
            it->second->processVoice(iVoice, in->clone());
            processVoiceChained(iVoice, it->second->getProcessed(iVoice));
        }
        const auto& res = shouldChainProcess ? getProcessedVoiceChained(iVoice) : in;
        /* now copying result into processed */
        PANTOUFLE_TRY_RETHROW({
            MidiNote::clone(lastProcessedNote, res);
        })
    }

    void
    MidiControllerChain::
    processVoiceChained(sizeint iVoice, const UPtr <MidiNote> &in)
    {
        if (!MidiNote::isNoteSet(in))
        {
            throw PANTOUFLE_EXCEPTION("Input note not set.");
        }
        auto it = _controllers.begin();
        const auto& end = _controllers.cend();
        ++it;
        /* */
        for (; it != end && std::next(it) != end; ++it)
        {
            /* if a controller is not set, we skip it */
            const auto &source = it->second;
            auto &dest = std::next(it)->second;
            PANTOUFLE_TRY_RETHROW({
                 dest->processVoiceChained(iVoice, source);
            })
        }
    }

    const UPtr<MidiNote>&
    MidiControllerChain::
    getProcessedVoiceChained(sizeint iVoice) const
    {
       if (_controllers.empty())
       {
           throw PANTOUFLE_EXCEPTION("Controller chain empty.");
       }
       return _controllers.crbegin()->second->getProcessed(iVoice);
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
