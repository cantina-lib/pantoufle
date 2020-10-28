//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTELAYER_HPP
#define CANTINA_TILDE_MIDINOTELAYER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

// interface
template <class Note_T> class MidiNoteLayerInterface {
public:
  /** -- methods  -- **/
  virtual ~MidiNoteLayerInterface() = default;

  CANT_NODISCARD virtual const Note_T &getVoice(size_u voice) const = 0;
  CANT_NODISCARD virtual size_u getNumberVoices() const = 0;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_TILDE_MIDINOTELAYER_HPP
