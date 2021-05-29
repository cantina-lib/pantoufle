//
// Created by binabik on 08/08/2020.
//

#ifndef CANTINA_PAN_MIDIPAN_HPP
#define CANTINA_PAN_MIDIPAN_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiPan : MultiMidiController<1> {
public:
  /** -- methods -- **/
  // factory method
  static ShPtr<MidiController> make(id_u8 channel, id_u8 controllerId);

private:
  /** -- methods -- **/
  MidiPan(id_u8 channel, id_u8 controllerId);

  CANT_NODISCARD pan_d getPan() const;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>
#endif // CANTINA_PAN_MIDIPAN_HPP
