//
// Created by binabik on 05/06/2020.
//

#ifndef CANTINA_PAN_MIDIDAMPER_HPP
#define CANTINA_PAN_MIDIDAMPER_HPP

#pragma once

#include <cant/pan/controller/MultiMidiController.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

class MidiDamper final : public MultiMidiController<1> {
public:
  /** -- methods **/
  MidiDamper(id_u8 channel, id_u8 controllerId);
  // factory method
  static ShPtr<MidiController> make(id_u8 channel, id_u8 controllerId);

  /**
   * Checks whether the Damper is currently been pressed.
   * @return
   */
  CANT_NODISCARD bool isOn() const;

private:
  /** -- methods **/

  // static methods
  CANT_NODISCARD static bool isOn(const MidiControlInternal &control);
};

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif // CANTINA_PAN_MIDIDAMPER_HPP
