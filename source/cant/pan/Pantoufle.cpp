//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/Pantoufle.hpp>

#include <cant/pan/common/PantoufleException.hpp>

#include <cant/time/InternalClock.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

Pantoufle::Pantoufle(size_u numberVoices, id_u8 channel)
    : m_timer(std::make_unique<MidiTimer>()),
      m_controllerChain(std::make_unique<ControllerManager>(numberVoices)),
      m_envelopeChain(std::make_unique<EnvelopeChain>(channel)),
      m_poly(
          std::make_unique<MidiNoteInputPoly>(numberVoices, channel, m_timer)),
      m_processedNoteInternal(
          std::make_unique<MidiNoteInternalLayer>(numberVoices)),
      m_processedNoteOutput(
          std::make_unique<MidiNoteOutputLayer>(numberVoices)) {
  // todo: move this to a Pantoufle::start function.
  m_timer->start();
}

void Pantoufle::update() {
  processAll();
  // update the timer AFTER processing the note!
  // because it resets the 'changed' flags of MidiNotes.
  m_timer->update();
}

size_u Pantoufle::getNumberVoices() const { return m_poly->getNumberVoices(); }

void Pantoufle::processEnvelopeChainVoice(size_u voice) {
  m_envelopeChain->process(m_processedNoteInternal->getVoiceMutable(voice));
}

void Pantoufle::receiveRawControlData(const MidiControlInputData &controlData) {
  const auto control = MidiControlInternal(controlData);
  m_controllerChain->receiveControl(control);
}

void Pantoufle::setCustomClock(time::AbsoluteTimeGetter absoluteTimeGetter) {
  m_timer->setCustomTimeGetter(std::move(absoluteTimeGetter));
}

Optional<size_u> Pantoufle::receiveInputNoteData(
    MidiNoteInputData const &inputData) {
  // processing will be done when time comes to updateDelta.
  return m_poly->receive(m_timer->getCurrentTime(), inputData);
}

void Pantoufle::process(size_u voice) {
  const MidiNoteInput &input = m_poly->getVoice(voice);
  const MidiNoteInternal &internal = m_processedNoteInternal->getVoice(voice);
  m_processedNoteInternal->receive(input);
  // processing controllers and envelope layer.
  processEnvelopeChainVoice(voice);
  //
  m_processedNoteOutput->receive(internal);
}

Stream<MidiNoteOutput> const &Pantoufle::getProcessedNoteOutput() const {
  return m_processedNoteOutput->getNotes();
}

MidiNoteOutput const &Pantoufle::getProcessedVoice(size_u voice) const {
  return m_processedNoteOutput->getVoice(voice);
}

void Pantoufle::processAll() {
  /*
   * Whatever the case, we will have to process the notes
   * each time we updateDelta, so no need to process them individually
   * when they are received.
   */
  // todo: multithread.
  for (size_u i = 0; i < getNumberVoices(); ++i) {
    process(i);
  }
}
void Pantoufle::addEnvelope(UPtr<MidiEnvelope> envelope) {
  auto &ref = m_envelopeChain->addEnvelope(std::move(envelope), m_timer);
  // add this envelope's controller to the chain if it has one.
  auto controller = ref->getController();
  if (controller) {
    m_controllerChain->addController(controller);
  }
}
CANTINA_PAN_NAMESPACE_END