//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_MIDICONTROLLER_HPP
#define CANTINA_MIDICONTROLLER_HPP

#pragma once

#include <cant/common/memory.hpp>
#include <cant/pan/common/types.hpp>

#include <cant/pan/controller/MidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiNoteInternal;

/**
 * MidiController should not grant unguarded access
 * to its Processor _memory to child classes.
 * It updates it, but can give a read-only ref.
 **/
template <size_u numberBindings>
class MultiMidiController : public MidiController {
public:
  CANT_NODISCARD Stream<id_u8> getControllerIds() const override;

protected:
  CANT_EXPLICIT MultiMidiController(id_u8 channel,
                                    Array<id_u8, numberBindings> controllerIds);

  CANT_NODISCARD const MidiControlInternal &getControl(size_u iControl) const;

private:
  /** -- methods -- **/
  // private inheritance
  void impl_receiveControl(const MidiControlInternal &incomingControl) final;

  /** -- fields -- **/
  id_u8 m_channel;
  Array<id_u8, numberBindings> m_controllerIds;
  Array<MidiControlInternal, numberBindings> m_controls;
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/controller/MultiMidiController.inl>

#endif // CANTINA_MIDICONTROLLER_HPP
