//
// Created by binabik on 05/06/2020.
//

#ifndef CANTINA_MIDIDAMPER_HPP
#define CANTINA_MIDIDAMPER_HPP

#pragma once

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiDamper final : public MultiMidiController<1> {
public:
  /** -- methods **/
  // factory method
  static UPtr<MidiController> make(size_u numberVoices, id_u8 channel,
                                   id_u8 controllerId);

private:
  /** -- methods **/
  MidiDamper(size_u numberVoices, id_u8 channel, id_u8 controllerId);

  CANT_NODISCARD bool isOn() const;
  // static methods
  CANT_NODISCARD static bool isOn(const MidiControlInternal &control);
  // event functions
  void
  beforeControlProcess(const MidiControlInternal &incomingControl) override;
  void beforeNoteProcess(const MidiNoteInternal &incomingNote) override;
  // private inheritance
  void IMPL_process(MidiNoteInternal &note) const override;

  /** -- fields **/
  /*
   * Can't be bool, since Stream are actually std::vector, and c++ does summat
   * funky with std::vector<bool> template specialisation.
   */
  Stream<id_u8> m_shouldHoldNotes;
  /*
   * It's not necessary to use this additional vector,
   * we could just use getMemory(iVoice).isPlaying().
   * However, I think that accessing the memory of the last processed notes
   * in the function in charge of processing is, in concept, a bad idea.
   * I'd rather save the values I'm interested in in the dedicated
   * function beforeNoteProcess(), where I get insurance
   * that this code will be executed *before* any new processing is done.
   */
  Stream<id_u8> m_isMemoryPlaying;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_MIDIDAMPER_HPP
