//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/common/PantoufleException.hpp>

namespace cant::pan
{
    Pantoufle::
    Pantoufle(const size_m numberVoices, const byte_m chanId)
    : _ctrlChain(numberVoices),
      _envlpLayer(numberVoices, chanId),
      _rawNoteInput(numberVoices),
      _processedNoteInternal(numberVoices),
      _processedNoteOutput(numberVoices),
      _rawControlInput()
    {
    }

    const Stream<MidiNoteOutput>&
    Pantoufle::
    getProcessedOutputData() const
    {
        return _processedNoteOutput;
    }

    void
    Pantoufle::
    update()
    {
        const time_m tCurrent = getCurrentTime();
        updateRawNoteInput(tCurrent);
        updateControlChain(tCurrent);
        updateEnvelopeLayer(tCurrent);
    }

    void
    Pantoufle::
    updateRawNoteInput(const time_m tCurrent)
    {
        for (auto& input : _rawNoteInput)
        {
            input.update(tCurrent);
        }
    }

    void
    Pantoufle::
    updateControlChain(const time_m tCurrent)
    {
        _ctrlChain.update(tCurrent);
    }

    void Pantoufle::
    updateEnvelopeLayer(const time_m tCurrent)
    {
         _envlpLayer.update(tCurrent);
    }

    time_m
    Pantoufle::
    getCurrentTime()
    {
        return Time::getCurrentTime();
    }

    size_m
    Pantoufle::
    getNumberVoices() const
    {
        return _rawNoteInput.size();
    }

    void
    Pantoufle::
    setController(UPtr<MidiController> controller)
    {
        const byte_m id = controller->getControllerId();
        PANTOUFLE_TRY_RETHROW({
             _ctrlChain.setController(std::move(controller));
             allocateControl(id);
        })
    }

    void
    Pantoufle::
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
    Pantoufle::
    receiveRawNoteData(const size_m iVoice, const MidiNoteInputData& inputData)
    {
        MidiNoteInput& input = _rawNoteInput.at(iVoice);
        input.update(inputData, getCurrentTime());
        process(iVoice);
    }

    void
    Pantoufle::
    process(const size_m iVoice)
    {
        const MidiNoteInput& input = _rawNoteInput.at(iVoice);
        MidiNoteInternal& internal = _processedNoteInternal.at(iVoice);
        MidiNoteOutput& output = _processedNoteOutput.at(iVoice);
        internal.update(input);
        /* updating controllers and envelope layer */
        processControllerChainVoice(iVoice);
        processEnvelopeLayerVoice(iVoice);
        /* */
        output.update(internal);
    }

    void
    Pantoufle::
    processControllerChainVoice(const size_m iVoice)
    {
        _ctrlChain.processVoice(iVoice, _processedNoteInternal.at(iVoice));
    }

    void
    Pantoufle::
    processControllerChainControl(const MidiControlInput& input)
    {
        _ctrlChain.processControl(input);
        /*
         * then we need to update the envelopes,
         * because the input (here ControlledNotes)
         * have changed.
         */
        for (size_m i = 0; i < getNumberVoices(); ++i)
        {
            process(i);
        }
    }

    void
    Pantoufle::
    processEnvelopeLayerVoice(const size_m iVoice)
    {
        _envlpLayer.processVoice(iVoice, _processedNoteInternal.at(iVoice));
    }


    void
    Pantoufle::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        /*
         * we do not throw if the controller is not recognised.
         * only ignore it.
         */
        const size_m controllerId = controlData.getControllerId();
        auto it = _rawControlInput.find(controllerId);
        if (it == _rawControlInput.end())
        {
            /*
             * not assigned to a controller, we ignore it
             */
            return;
        }
        MidiControlInternal& control = _rawControlInput.at(controllerId);
        control = MidiControlInput(controlData);
        /*
         * processing all the notes again
         */
        processControllerChainControl(control);
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
