//
// Created by binabik on 02/06/2020.
//

#ifndef CANTINA_RAWMIDNOTE_HPP
#define CANTINA_RAWMIDNOTE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteData.hpp>
#include <cant/pan/note/MidiNote.hpp>

namespace cant::midi
{


    class RawMidiNote final : public MidiNote
    {
        friend MidiNote;
    private:
        MidiNoteInput _input;

        bool _flagSet;

    private: // used by MidiNote
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override;
        CANT_NODISCARD bool justChanged() const override;
        CANT_NODISCARD bool isNew(const UPtr<MidiNote>&) const override;

        CANT_NODISCARD std::string print() const override;

        CANT_EXPLICIT RawMidiNote(const MidiNoteInput& input);
    protected:
        CANT_NODISCARD bool isExtensible() const override { return true; };

        CANT_NODISCARD CANT_INLINE time_m getStartingTime() const final;
        void reset(const UPtr<MidiNote>& note) override;
        void reset() override;

        CANT_NODISCARD CANT_INLINE vel_m getVelocity() const override;

        CANT_MAYBEUNUSED void update(const UPtr<MidiNote> &note) override;
        CANT_MAYBEUNUSED void update(time_m tCurrent) override;
        CANT_MAYBEUNUSED void set(const UPtr<MidiNote> &note) override;

    public:
        CANT_NODISCARD CANT_INLINE bool isPressed() const override;
        CANT_NODISCARD CANT_INLINE bool isPlaying() const override;

        CANT_NODISCARD CANT_INLINE time_m getTone() const override;
        CANT_NODISCARD CANT_INLINE byte_m getChannel() const override;

        CANT_NODISCARD const MidiNoteInput& getInputData() const override;

        CANT_NODISCARD CANT_INLINE bool isSet() const override;

        CANT_NODISCARD static UPtr<MidiNote> make(const MidiNoteInput &input);
    };
}

#endif //CANTINA_RAWMIDNOTE_HPP
