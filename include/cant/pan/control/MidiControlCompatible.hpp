//
// Created by binabik on 22/07/2020.
//

#ifndef CANTINA_MIDICONTROLCOMPATIBLE_HPP
#define CANTINA_MIDICONTROLCOMPATIBLE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiControlCompatible {
public:
  /** -- methods -- **/
  virtual ~MidiControlCompatible() = default;

  CANT_NODISCARD virtual id_u8 getChannel() const = 0;
  CANT_NODISCARD virtual id_u8 getId() const = 0;
  CANT_NODISCARD virtual id_u8 getValue() const = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_MIDICONTROLCOMPATIBLE_HPP
