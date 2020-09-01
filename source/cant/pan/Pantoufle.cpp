//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/processor/processor.hpp>
#include <cant/pan/layer/layer.hpp>

#include <cant/pan/controller/MidiController.hpp>
#include <cant/pan/control/MidiControlData.hpp>
#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>
#include <cant/pan/time/MidiTimer.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    Pantoufle::
    Pantoufle(const size_m numberVoices, const byte_m channel)
    : m_controllerChain(std::make_unique<MidiControllerChain>(numberVoices)),
      m_envelopeLayer(std::make_unique<MidiEnvelopeLayer>(numberVoices, channel)),
      m_poly(std::make_unique<MidiNoteInputPoly>(numberVoices, channel)),
      m_processedNoteInternal(std::make_unique<MidiNoteInternalLayer>(numberVoices)),
      m_processedNoteOutput(std::make_unique<MidiNoteOutputLayer>(numberVoices))
    {

    }

    const Stream<MidiNoteOutput>&
    Pantoufle::
    getProcessedOutputData() const
    {
        return m_processedNoteOutput->getNotes();
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
        m_poly->flushChange();
    }

    void
    Pantoufle::
    flushChangeEnvelopeLayer()
    {
        m_envelopeLayer->flushChange();
    }


    void
    Pantoufle::
    updateControlChain(const time_m tCurrent)
    {
        m_controllerChain->update(tCurrent);
    }

    void Pantoufle::
    updateEnvelopeLayer(const time_m tCurrent)
    {
         m_envelopeLayer->update(tCurrent);
    }

    time_m
    Pantoufle::
    getCurrentTime() const
    {
        return m_timer->getCurrentTime();
    }

    size_m
    Pantoufle::
    getNumberVoices() const
    {
        return m_poly->getNumberVoices();
    }

    void
    Pantoufle::
    setController(UPtr<MidiController> controller)
    {
        PANTOUFLE_TRY_RETHROW({
                                  m_controllerChain->addController(std::move(controller));
        })
    }


    void
    Pantoufle::
    receiveInputNoteData(const MidiNoteInputData& inputData)
    {
        m_poly->receive(getCurrentTime(), inputData);
        /* processing will be done when time comes to update. */
    }

    void
    Pantoufle::
    process(const size_m voice)
    {
        const MidiNoteInput& input = m_poly->getVoice(voice);
        m_processedNoteInternal->receive(input);
        /* processing controllers and envelope layer */
        processControllerChainVoice(voice);
        processEnvelopeLayerVoice(voice);
        /* */
        const MidiNoteInternal& internal = m_processedNoteInternal->getVoice(voice);
        m_processedNoteOutput->receive(internal);
    }

    void
    Pantoufle::
    processControllerChainVoice(const size_m voice)
    {
        m_controllerChain->process(m_processedNoteInternal->getVoiceMutable(voice));
    }

    void
    Pantoufle::
    processEnvelopeLayerVoice(const size_m voice)
    {
        m_envelopeLayer->process(m_processedNoteInternal->getVoiceMutable(voice));
    }


    void
    Pantoufle::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        const auto control = MidiControlInternal(controlData);
        m_controllerChain->receiveControl(control);
    }
}
