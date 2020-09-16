//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/processor/processor.hpp>
#include <cant/pan/layer/layer.hpp>

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

    void
    Pantoufle::
    setController(UPtr<MidiController> controller)
    {
        PANTOUFLE_TRY_RETHROW({
              m_controllerChain->addController(std::move(controller));
        })
    }


    Optional<size_u>
    Pantoufle::
    receiveInputNoteData(const MidiNoteInputData& inputData)
    {
        /* processing will be done when time comes to update. */
        return m_poly->receive(getCurrentTime(), inputData);
    }

    void
    Pantoufle::
    process(const size_u voice)
    {
        const MidiNoteInput& input = m_poly->getVoice(voice);
        const MidiNoteInternal& internal = m_processedNoteInternal->getVoice(voice);
        m_processedNoteInternal->receive(input);
        /* processing controllers and envelope layer */
        processControllerChainVoice(voice);
        processEnvelopePairVoice(voice);
        /* */
        m_processedNoteOutput->receive(internal);
    }

}
