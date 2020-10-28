
#ifndef CANTINA_PAN_MIDIPROCESSORMEMORY_HPP
#define CANTINA_PAN_MIDIPROCESSORMEMORY_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/layer/MidiNoteInternalLayer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiProcessorMemory : public MidiProcessor {
public:
  /** -- methods -- **/
  CANT_EXPLICIT MidiProcessorMemory(size_u numberVoices);

  void process(MidiNoteInternal &in) override = 0;

  CANT_NODISCARD size_u getNumberVoices() const;

protected:
  /** -- fields -- **/
  MidiNoteInternalLayer m_memory;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/processor/MidiProcessorMemory.inl>

#endif // CANTINA_PAN_MIDIPROCESSORMEMORY_HPP