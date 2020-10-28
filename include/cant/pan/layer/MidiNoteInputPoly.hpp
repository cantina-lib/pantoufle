//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP
#define CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/layer/MidiNoteInputLayer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiTimer;

class MidiNoteInputPoly : public MidiNoteInputLayer {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiNoteInputPoly(size_u numberVoices, id_u8 channel,
                                  UPtr<MidiTimer> &timer);

  Optional<size_u> receive(time_d tCurrent,
                           const MidiNoteInputData &data) override;

private:
  /** -- methods -- **/
  CANT_NODISCARD Optional<size_u>
  chooseVoice(const MidiNoteInputData &data) const;

  /** -- fields **/
  id_u8 m_channel;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP
