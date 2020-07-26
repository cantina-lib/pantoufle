//
// Created by binabik on 04/06/2020.
//

#ifndef CANTINA_DAMPMIDINOTE_HPP
#define CANTINA_DAMPMIDINOTE_HPP

#pragma once


#include <cant/pan/common/types.hpp>
#include <cant/pan/note/ControlledMidiNote.hpp>

namespace cant::midi
{
     class DampMidiNote final : public ControlledMidiNote
     {
     private:
         bool _flagShouldHold;
     private:
         CANT_NODISCARD bool isOn() const;
     private: // unusable here, used by base class
         CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override;
         CANT_NODISCARD bool justChanged() const override;

         void onControlChange() override;

         CANT_EXPLICIT DampMidiNote(WPtr<MidiControl> control);
         CANT_NODISCARD std::string print() const override;
     protected:
         void set(const UPtr<MidiNote> &baseNote) override;

         void update(const UPtr<MidiNote> &baseNote) override;
     public:
         CANT_NODISCARD bool isPlaying() const override;

         CANT_NODISCARD tone_m getTone() const override;
         CANT_NODISCARD vel_m getVelocity() const override;


         CANT_NODISCARD static UPtr<ControlledMidiNote> make(WPtr<MidiControl> control);
     };
}

#endif //CANTINA_DAMPMIDINOTE_HPP
