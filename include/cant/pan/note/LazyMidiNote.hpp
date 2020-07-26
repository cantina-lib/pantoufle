//
// Created by binabik on 20/07/2020.
//

#ifndef CANTINA_LAZYMIDINOTE_HPP
#define CANTINA_LAZYMIDINOTE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/DecoratedMidiNote.hpp>

namespace cant::midi
{
    /**
     * A kind of MidiNote which entirely delegqtes its behaviour to its base
     * Think lazy
     * Can be used to provide an empty container for
     * a decorated pan note that's not yet set.
     **/
    class LazyMidiNote final : public DecoratedMidiNote
    {
    private:
        LazyMidiNote() = default;
    private: // unusable here, used by base class
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override;
        CANT_NODISCARD bool justChanged() const override;
    protected:
        CANT_NODISCARD bool isExtensible() const override;
    public:
        CANT_NODISCARD bool isPlaying() const override;

        CANT_NODISCARD tone_m getTone() const override;
        CANT_NODISCARD vel_m getVelocity() const override;

        CANT_NODISCARD static UPtr<LazyMidiNote> make();
    };
}

#endif //CANTINA_LAZYMIDINOTE_HPP
