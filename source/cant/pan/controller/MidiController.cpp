//
// Created by piptouque on 29/04/2020.
//

#include <cant/pan/controller/MidiController.hpp>
#include <cant/pan/note/ControlledMidiNote.hpp>

namespace cant::midi
{
    MidiController::
    MidiController(const sizeint numberVoices, const byte_m channel, const byte_m id)
            : MidiProcessorMemoryProxy(numberVoices),
            _channel(channel),
            _controllerId(id),
            _control(MidiControl::makeShared())
    {
        /*
         * allocateProcessed can't be called here -> virtual
         * must be called in child classes
         */
    }

    void
    MidiController::
    allocateProcessed()
    {
        for(auto& note: _processed)
        {
            note = allocateNote(getControlWeak());
        }
    }

    bool
    MidiController::
    isSet() const
    {
        return isControlSet();
    }

    bool
    MidiController::
    isControlSet() const
    {
        return MidiControl::isControlSet(_control);
    }
    bool
    MidiController::
    isControllerSet(const MidiController* controller)
    {
        return static_cast<bool>(controller) && controller->isSet();
    }

    bool
    MidiController::
    isControllerSet(const UPtr<MidiController>& controller)
    {
        return isControllerSet(controller.get());
    }


    void
    MidiController::
    receiveControl(const MidiControlInput& input)
    {
        if (!isControlSet() && !isSet())
        {
           throw PANTOUFLE_EXCEPTION("Controller not set.");
        }
        MidiControl::update(_control, input);
        notifyProcessedOnChange();
    }

    void
    MidiController::
    notifyProcessedOnChange()
    {
        for (auto& note : _processed)
        {
            if (MidiNote::isNoteSet(note))
            {
                note->onControlChange();
            }
        }
    }

    const ShPtr<MidiControl>&
    MidiController::
    getControlShared() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Controller not set.");
        }
        return _control;
    }

    WPtr<MidiControl>
    MidiController::
    getControlWeak() const
    {
        if (!isSet())
        {
            throw PANTOUFLE_EXCEPTION("Controller not set.");
        }
        return _control;
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
        out << controller->getControlShared();
        return out;
    }

    std::ostream&
    operator<<(std::ostream& out, const UPtr<MidiController>& controller)
    {
        return out << controller.get();
    }

    void
    MidiController::
    processVoiceChained(const sizeint iVoice, const UPtr<MidiController> &source)
    {
        /*
         * TODO: if process was a template, we wouldn't have to clone the note!
         */
        const auto& in = source->_processed.at(iVoice);
        if (MidiNote::isNoteSet(in))
        {
            PANTOUFLE_TRY_RETHROW({
                processVoice(iVoice, in->clone());
             })
        }
    }

    void
    MidiController::
    processVoice(const sizeint iVoice, const UPtr<MidiNote> &in)
    {
        if (!MidiNote::isNoteSet(in))
        {
           throw PANTOUFLE_EXCEPTION("Received note not set");
        }

        // std::cout << "ctr: " << in << std::endl;
        auto& out = _processed.at(iVoice);
        PANTOUFLE_TRY_RETHROW({
             out->updateElseSet(in);
         })
        // std::cout << "out: " << out << std::endl;
    }
}

