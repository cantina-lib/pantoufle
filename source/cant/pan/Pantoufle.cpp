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
        updateControlChain(tCurrent);
        updateEnvelopeLayer(tCurrent);
        processAll();
        /**
         * ++IMPORTANT
         * Raw input has got to be updated last,
         * because it discards its 'changed' state,
         * and the info is never received by the processors.
         **/
         flushChange();
    }

    void
    Pantoufle::
    processAll()
    {
        /*
         * Whatever the case, we will have to process the notes
         * each time we update, so no need to do process them individually
         * when they are received.
         */
        for (size_m i = 0; i < getNumberVoices(); ++i)
        {
            process(i);
        }
    }

    void
    Pantoufle::
    flushChange()
    {
        flushChangeRawNoteInput();
        flushChangeEnvelopeLayer();
    }

    void
    Pantoufle::
    flushChangeRawNoteInput()
    {
        for(auto& input : _rawNoteInput)
        {
            input.flushChange();
        }
    }

    void
    Pantoufle::
    flushChangeEnvelopeLayer()
    {
        _envlpLayer.flushChange();
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
    getCurrentTime() const
    {
        return _timer.getCurrentTime();
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
        input.set(getCurrentTime(), inputData);
        /* processing will be done when time comes to update. */
    }

    void
    Pantoufle::
    process(const size_m iVoice)
    {
        const MidiNoteInput& input = _rawNoteInput.at(iVoice);
        MidiNoteInternal& internal = _processedNoteInternal.at(iVoice);
        MidiNoteOutput& output = _processedNoteOutput.at(iVoice);
        internal.set(input);
        /* processing controllers and envelope layer */
        processControllerChainVoice(iVoice);
        processEnvelopeLayerVoice(iVoice);
        /* */
        output.set(internal);
    }

    void
    Pantoufle::
    processControllerChainVoice(const size_m iVoice)
    {
       _ctrlChain.processVoice(iVoice, _processedNoteInternal.at(iVoice));
    }

    void
    Pantoufle::
    processControllerChainControl(const MidiControlInternal& input)
    {
        _ctrlChain.processControl(input);
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
        processControllerChainControl(control);
    }


}
