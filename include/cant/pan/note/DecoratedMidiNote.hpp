//
// Created by binabik on 04/06/2020.
//

#ifndef CANTINA_DECORATEDMIDINOTE_HPP
#define CANTINA_DECORATEDMIDINOTE_HPP

#pragma once


#include <cant/pan/common/types.hpp>
#include <cant/pan/note/MidiNote.hpp>

namespace cant::pan
{
    class DecoratedMidiNote : public MidiNote
    {
        friend class MidiNote;
    private:
        UPtr<MidiNote> _base;
    private: // unusable here, used by base class
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override = 0;
        CANT_NODISCARD bool justChanged() const override = 0;
        CANT_NODISCARD bool isNew(const UPtr<MidiNote>& note) const override;


    protected:
        CANT_NODISCARD bool isExtensible() const override = 0;
        /* @brief: updates current note and state. Should be called at every iteration */
        void update(const UPtr<MidiNote> &) override;

        void reset(const UPtr<MidiNote>& base) override;
        void reset() override;

        void set(const UPtr<MidiNote> &base) override;

        CANT_NODISCARD bool isSet() const override;

        CANT_NODISCARD bool isBasePlaying() const;
        CANT_NODISCARD bool isBaseSet() const;
        CANT_NODISCARD bool isBaseExtensible() const;
        CANT_NODISCARD const UPtr<MidiNote>& getBase() const;
        virtual void setBase(const UPtr <MidiNote> &base);
        CANT_NODISCARD bool hasBaseJustChanged() const;

        CANT_NODISCARD vel_m getVelocity() const override = 0;
        CANT_NODISCARD vel_m getBaseVelocity() const;
        CANT_NODISCARD time_m getStartingTime() const final;

        CANT_NODISCARD std::string print() const override;

        DecoratedMidiNote(const DecoratedMidiNote&);
        DecoratedMidiNote() = default;
        explicit DecoratedMidiNote(const UPtr<MidiNote>& base);
    public:
        void update(time_m tCurrent) override;
        /* for ADSR MidiEnvelope */
        CANT_NODISCARD bool hasBaseJustStarted() const;
        CANT_NODISCARD bool hasBaseJustStopped() const;
        /* for FlatTone MidiEnvelope */
        CANT_NODISCARD tone_m getBaseTone() const;

        CANT_NODISCARD bool isPlaying() const override = 0;
        CANT_NODISCARD bool isPressed() const override;

        CANT_NODISCARD tone_m getTone() const override = 0;
        CANT_NODISCARD byte_m getChannel() const override;

        CANT_NODISCARD const MidiNoteInput& getInputData() const final;


    };
}

#endif //CANTINA_DECORATEDMIDINOTE_HPP
