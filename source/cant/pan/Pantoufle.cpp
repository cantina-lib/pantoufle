//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/pan/common/PantoufleException.hpp>

// shouldn't have to include this..
#include <cant/time/InternalClock.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

Pantoufle::Pantoufle(size_u numberVoices, id_u8 channel)
    : m_timer(std::make_unique<MidiTimer>()),
      m_controllerChain(std::make_unique<MidiControllerChain>(numberVoices)),
      m_envelopePair(
          std::make_unique<MidiEnvelopePair>(numberVoices, channel, m_timer)),
      m_poly(
          std::make_unique<MidiNoteInputPoly>(numberVoices, channel, m_timer)),
      m_processedNoteInternal(
          std::make_unique<MidiNoteInternalLayer>(numberVoices)),
      m_processedNoteOutput(
          std::make_unique<MidiNoteOutputLayer>(numberVoices)) {
  m_timer->start();
}

UPtr<Pantoufle> Pantoufle::make(size_u numberVoices, id_u8 channel) {
  return UPtr<Pantoufle>(new Pantoufle(numberVoices, channel));
}

void Pantoufle::update() {
  m_timer->update();
  processAll();
}

time_d Pantoufle::getCurrentTime() const { return m_timer->getCurrentTime(); }

size_u Pantoufle::getNumberVoices() const { return m_poly->getNumberVoices(); }

void Pantoufle::processControllerChainVoice(const size_u voice) {
  m_controllerChain->process(m_processedNoteInternal->getVoiceMutable(voice));
}

void Pantoufle::processEnvelopePairVoice(const size_u voice) {
  m_envelopePair->process(m_processedNoteInternal->getVoiceMutable(voice));
}

void Pantoufle::receiveRawControlData(const MidiControlInputData &controlData) {
  const auto control = MidiControlInternal(controlData);
  m_controllerChain->receiveControl(control);
}

void Pantoufle::setCustomClock(time::AbsoluteTimeGetter absoluteTimeGetter) {
  m_timer->setCustomTimeGetter(std::move(absoluteTimeGetter));
}

void Pantoufle::setController(UPtr<MidiController> controller){
    PANTOUFLE_TRY_RETHROW({
      m_controllerChain->addController(std::move(controller));
    })}

Optional<size_u> Pantoufle::receiveInputNoteData(
    const MidiNoteInputData &inputData) {
  /* processing will be done when time comes to updateDelta. */
  return m_poly->receive(getCurrentTime(), inputData);
}

void Pantoufle::process(const size_u voice) {
  const MidiNoteInput &input = m_poly->getVoice(voice);
  const MidiNoteInternal &internal = m_processedNoteInternal->getVoice(voice);
  m_processedNoteInternal->receive(input);
  /* processing controllers and envelope layer */
  processControllerChainVoice(voice);
  processEnvelopePairVoice(voice);
  /* */
  m_processedNoteOutput->receive(internal);
}

const Stream<MidiNoteOutput> &Pantoufle::getProcessedNoteOutput() const {
  return m_processedNoteOutput->getNotes();
}

const MidiNoteOutput &Pantoufle::getProcessedVoice(size_u voice) const {
  return m_processedNoteOutput->getVoice(voice);
}

void Pantoufle::processAll() {
  /*
   * Whatever the case, we will have to process the notes
   * each time we updateDelta, so no need to process them individually
   * when they are received.
   */
  for (size_u i = 0; i < getNumberVoices(); ++i) {
    process(i);
  }
}

CANTINA_PAN_NAMESPACE_END