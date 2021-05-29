//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_PAN_FLATTONEENVELOPE_HPP
#define CANTINA_PAN_FLATTONEENVELOPE_HPP

#pragma once

#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan {
class FlatToneEnvelope final : public MidiEnvelope {
public:
  /** -- methods -- **/
  // factory method
  static UPtr<MidiEnvelope> make();

  void process(MidiNoteInternal &note) override;
};
} // namespace cant::pan
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_FLATTONEENVELOPE_HPP
