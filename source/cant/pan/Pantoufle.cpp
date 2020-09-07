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
    Pantoufle(const size_u numberVoices, const id_u8 channel)
    : m_controllerChain(std::make_unique<MidiControllerChain>(numberVoices)),
      m_envelopePair(std::make_unique<MidiEnvelopePair>(numberVoices, channel)),
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
        const time_d tCurrent = getCurrentTime();
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
        for (size_u i = 0; i < getNumberVoices(); ++i)
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
        m_envelopePair->flushChange();
    }


    void
    Pantoufle::
    updateControlChain(const time_d tCurrent)
    {
        m_controllerChain->update(tCurrent);
    }

    void Pantoufle::
    updateEnvelopeLayer(const time_d tCurrent)
    {
         m_envelopePair->update(tCurrent);
    }

    time_d
    Pantoufle::
    getCurrentTime() const
    {
        return m_timer->getCurrentTime();
    }

    size_u
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
    process(const size_u voice)
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
    processControllerChainVoice(const size_u voice)
    {
        m_controllerChain->process(m_processedNoteInternal->getVoiceMutable(voice));
    }

    void
    Pantoufle::
    processEnvelopeLayerVoice(const size_u voice)
    {
        m_envelopePair->process(m_processedNoteInternal->getVoiceMutable(voice));
    }


    void
    Pantoufle::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        const auto control = MidiControlInternal(controlData);
        m_controllerChain->receiveControl(control);
    }
}
