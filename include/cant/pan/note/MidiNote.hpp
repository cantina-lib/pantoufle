//
// Created by binabik on 01/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTE_HPP
#define CANTINA_TILDE_MIDINOTE_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>
#include <cant/pan/note/MidiNoteData.hpp>


#include <cant/common/macro.hpp>
namespace cant::pan
{

    template <class Data_T>
    class MidiNote : MidiNoteCompatible
    {
    protected:
        Data_T _data;
        size_m _voice;
        time_m _tStart;
    public:
        /*
         * todo: get undefined symbol when defining abstract destructor here
         * probably has to do with template, when instantiating it... whatever,
         * it'll have to be concrete.
         */
        MidiNote(size_m voice, byte_m channel, tone_m tone, vel_m velocity);

        CANT_EXPLICIT MidiNote(size_m voice);

        CANT_NODISCARD const Data_T& getData() const;

        CANT_NODISCARD size_m getVoice() const;

        CANT_NODISCARD byte_m getChannel() const override;
        CANT_NODISCARD tone_m getTone() const override;
        CANT_NODISCARD vel_m getVelocity() const override;

        CANT_NODISCARD time_m getStartingTime() const override;
    };


    class MidiNoteInput : public MidiNote<MidiNoteInputData>, MidiNoteInputCompatible
    {
    private:
        bool _isPressed;
        bool _flagChangedPlaying;
        bool _flagChangedTone;
    private:
        void raiseFlagChangedPlaying();
        void raiseFlagChangedNote();
        void discardAllChangeFlags();

        CANT_CONSTEXPR MidiNoteInput(const MidiNoteInput&) = default;
        CANT_NODISCARD  MidiNoteInput& operator=(const MidiNoteInput&) = default;

        MidiNoteInput(size_m voice, byte_m channel, tone_m tone, vel_m velocity, bool isPressed);
    public:
        CANT_EXPLICIT MidiNoteInput(size_m voice);

        CANT_CONSTEXPR MidiNoteInput(MidiNoteInput&&) = default;

        void set(time_m tCurrent, const MidiNoteInputData& data);

        void flushChange();

        CANT_NODISCARD bool isPressed() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;
    };


    class MidiNoteInternal : public MidiNote<MidiNoteInternalData>, MidiNoteInternalCompatible
    {
    private:
        bool _isPlaying;
        bool _justChangedPlaying;
        bool _justChangedTone;

    public:
        CANT_EXPLICIT MidiNoteInternal(size_m voice);

        void set(const MidiNoteInput& input);

        CANT_NODISCARD time_m getLength(time_m tCurrent) const override;

        void setPlaying(bool isPlaying);
        void setChangedPlaying(bool justChanged);
        void setChangedTone(bool justChanged);

        void setTone(tone_m tone) override;
        void setVelocity(vel_m velocity) override;
        void setPan(pan_m pan) override;

        CANT_NODISCARD pan_m getPan() const override;

        CANT_NODISCARD bool isPlaying() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;

    };

    class MidiNoteOutput : public MidiNote<MidiNoteOutputData>, MidiNoteOutputCompatible
    {
    private:
        bool _isPlaying;
        bool _justChangedPlaying;
        bool _justChangedTone;
    private:
        CANT_NODISCARD vel_m getVelocity() const override;

    public:
        CANT_EXPLICIT MidiNoteOutput(size_m voice);

        void set(const MidiNoteInternal& internal);

        CANT_NODISCARD time_m getLength(time_m tCurrent) const override;

        CANT_NODISCARD vel_m getVelocityPlaying() const override;
        CANT_NODISCARD Array<vel_m, 2> getVelocityPanned() const override;

        CANT_NODISCARD pan_m getPan() const override;

        CANT_NODISCARD bool isPlaying() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;

        CANT_NODISCARD bool justStarted() const;
        CANT_NODISCARD bool justStopped() const;

    };
}

#include <cant/common/undef_macro.hpp>

#include "MidiNote.inl"

#endif //CANTINA_TILDE_MIDINOTE_HPP
