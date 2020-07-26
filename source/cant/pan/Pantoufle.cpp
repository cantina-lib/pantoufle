//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/PantoufleException.hpp>

namespace cant::midi
{
    MidiMachine::
    MidiMachine(const sizeint numberVoices, const byte_m chanId)
    : _ctrlChain(numberVoices),
      _envlpLayer(numberVoices, chanId),
      _rawNoteInput(numberVoices),
      _rawNotes(numberVoices),
      _processedNoteOutput(numberVoices),
      _rawControlInput()
    {
    }

    const Stream<MidiNoteOutput>&
    MidiMachine::
    getProcessedOutputData() const
    {
        sizeint i = 0;
        for (auto& output : _processedNoteOutput)
        {
            const auto& note = _envlpLayer.getProcessed(i);
            if (MidiNote::isNoteSet(note))
            {
                output = note->getOutput();
            }
            else
            {
                output = MidiNoteOutput();
            }
            ++i;
        }
        return _processedNoteOutput;
    }

    void
    MidiMachine::
    update()
    {
        CANT_MAYBEUNUSED const auto& input = _rawNoteInput.front();
        const UPtr<MidiNote> raw =  RawMidiNote::make(input);
        CANT_MAYBEUNUSED const auto& controlled = _ctrlChain.getProcessed(0);
        CANT_MAYBEUNUSED const auto& enveloped = _envlpLayer.getProcessed(0);
        // std::cout << "input: " << input << std::endl;
        // std::cout << "raw: " << raw << std::endl;
        // std::cout << "controlled: " << controlled << std::endl;
        // std::cout << "enveloped" << _envlpLayer.getProcessed(0) << std::endl;
        updateRawNotes();
        updateControlChain();
        updateEnvelopes();
    }

    void
    MidiMachine::
    updateRawNotes()
    {
        for (auto& note : _rawNotes)
        {
            if (MidiNote::isNoteSet(note))
            {
                note->update(getCurrentTime());
            }
        }

    }

    void
    MidiMachine::
    updateControlChain()
    {
        PANTOUFLE_TRY_RETHROW({
            _ctrlChain.update(getCurrentTime());
        })
    }

    void MidiMachine::
    updateEnvelopes()
    {
        PANTOUFLE_TRY_RETHROW({
             _envlpLayer.update(getCurrentTime());
        })
    }

    time_m
    MidiMachine::
    getCurrentTime()
    {
        return Time::getCurrentTime();
    }

    sizeint
    MidiMachine::
    getNumberVoices() const
    {
        return _rawNoteInput.size();
    }

    void
    MidiMachine::
    setController(UPtr<MidiController> controller)
    {
        const byte_m id = controller->getControllerId();
        PANTOUFLE_TRY_RETHROW({
             _ctrlChain.setController(std::move(controller));
             allocateControl(id);
        })
    }

    void
    MidiMachine::
    allocateControl(const byte_m controllerId)
    {
        auto it = _rawControlInput.find(controllerId);
        /* if control not already set */
        if(it == _rawControlInput.end())
        {
            _rawControlInput.insert
            (
                std::pair<byte_m, MidiControlInput>(controllerId, MidiControlInput())
            );
        }
    }

    void
    MidiMachine::
    receiveRawNoteData(const sizeint iVoice, const MidiNoteInputData& noteData)
    {
        _rawNoteInput.at(iVoice).update(noteData, getCurrentTime());
        _rawNotes.at(iVoice) = RawMidiNote::make(_rawNoteInput.at(iVoice));
        PANTOUFLE_TRY_RETHROW({
             /* updating controls (and thus everything else) */
             process(iVoice);
        })
    }

    void
    MidiMachine::
    process(const sizeint iVoice)
    {
        processControllerChainVoice(iVoice);
        processEnvelopeLayerVoice(iVoice);
    }

    void
    MidiMachine::
    processControllerChainVoice(const sizeint iVoice)
    {
        _ctrlChain.processVoice(iVoice, _rawNotes.at(iVoice));
    }

    void
    MidiMachine::
    processControllerChainControl(const MidiControlInput& input)
    {
        _ctrlChain.processControl(input, _rawNotes);
        /*
         * then we need to update the envelopes,
         * because the input (here ControlledNotes)
         * have changed.
         */
        for (sizeint i = 0; i < getNumberVoices(); ++i)
        {
            // process(i);
        }
    }

    void
    MidiMachine::
    processEnvelopeLayerVoice(const sizeint iVoice)
    {
        _envlpLayer.processVoice(iVoice, _ctrlChain.getProcessed(iVoice));
        _processedNoteOutput.at(iVoice) = _envlpLayer.getProcessed(iVoice)->getOutput();
    }


    void
    MidiMachine::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        /*
         * we do not throw if the controller is not recognised.
         * only ignore it.
         */
        const sizeint controllerId = controlData.getControllerId();
        auto it = _rawControlInput.find(controllerId);
        if (it == _rawControlInput.end())
        {
            /*
             * not assigned to a controller, we ignore it
             */
            return;
        }
        _rawControlInput.at(controllerId) = MidiControlInput(controlData);
        /*
         * processing all the notes again
         */
        processControllerChainControl(_rawControlInput.at(controllerId));
        /*
         * No need to compute everything again,
         * the notes have access to their control and can
         * adjust on their own.
	 * YOU WISH
	 * well, if every smart pointer wasn't deep-copied,
	 * it would indeed be the case
	 * Tough luck.
         */
    }


}
