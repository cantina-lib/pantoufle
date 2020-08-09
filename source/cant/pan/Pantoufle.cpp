//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/common/PantoufleException.hpp>

namespace cant::pan
{
    Pantoufle::
    Pantoufle(const size_m numberVoices, const byte_m channel)
    : _ctrlChain(numberVoices),
      _envlpLayer(numberVoices, channel),
      _poly(numberVoices, channel),
      _processedNoteInternal(numberVoices),
      _processedNoteOutput(numberVoices)
    {

    }

    const Stream<MidiNoteOutput>&
    Pantoufle::
    getProcessedOutputData() const
    {
        return _processedNoteOutput.getNotes();
    }

    void
    Pantoufle::
    update()
    {
        const time_m tCurrent = getCurrentTime();
        updateControlChain(tCurrent);
        updateEnvelopeLayer(tCurrent);
        processAll();
        flushChange();
    }

    void
    Pantoufle::
    processAll()
    {
        /*
         * Whatever the case, we will have to process the notes
         * each time we update, so no need to process them individually
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
        flushChangeNoteInput();
        flushChangeEnvelopeLayer();
    }

    void
    Pantoufle::
    flushChangeNoteInput()
    {
        _poly.flushChange();
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
        return _poly.getNumberVoices();
    }

    void
    Pantoufle::
    setController(UPtr<MidiController> controller)
    {
        PANTOUFLE_TRY_RETHROW({
                                  _ctrlChain.addController(std::move(controller));
        })
    }


    void
    Pantoufle::
    receiveInputNoteData(const MidiNoteInputData& inputData)
    {
        _poly.receive(getCurrentTime(), inputData);
        /* processing will be done when time comes to update. */
    }

    void
    Pantoufle::
    process(const size_m voice)
    {
        const MidiNoteInput& input = _poly.get(voice);
        _processedNoteInternal.receive(input);
        /* processing controllers and envelope layer */
        processControllerChainVoice(voice);
        processEnvelopeLayerVoice(voice);
        /* */
        const MidiNoteInternal& internal = _processedNoteInternal.get(voice);
        _processedNoteOutput.receive(internal);
    }

    void
    Pantoufle::
    processControllerChainVoice(const size_m voice)
    {
        _ctrlChain.process(_processedNoteInternal.getMutable(voice));
    }

    void
    Pantoufle::
    processEnvelopeLayerVoice(const size_m voice)
    {
        _envlpLayer.process(_processedNoteInternal.getMutable(voice));
    }


    void
    Pantoufle::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        const auto control = MidiControlInternal(controlData);
        _ctrlChain.receiveControl(control);
    }


}
