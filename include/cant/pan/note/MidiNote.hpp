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
    public:
        /** -- methods -- **/
        /*
         * todo: get undefined symbol when defining abstract destructor here
         * probably has to do with template, when instantiating it... whatever,
         * it'll have to be concrete.
         */
        MidiNote(size_u voice, id_u8 channel, tone_d tone, vel_d velocity);
        CANT_EXPLICIT MidiNote(size_u voice);

        CANT_NODISCARD const Data_T& getData() const;

        CANT_NODISCARD size_u getVoice() const;

        CANT_NODISCARD id_u8 getChannel() const override;
        CANT_NODISCARD tone_d getTone() const override;
        CANT_NODISCARD vel_d getVelocity() const override;

        CANT_NODISCARD time_d getStartingTime() const override;
    protected:
        /** -- fields -- **/
        Data_T m_data;
        size_u m_voice;
        time_d m_tStart;
    };


    class MidiNoteInput : public MidiNote<MidiNoteInputData>, MidiNoteInputCompatible
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteInput(size_u voice);

        void set(time_d tCurrent, const MidiNoteInputData& data);

        void flushChange();

        CANT_NODISCARD bool isPressed() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;
    private:
        /** -- methods -- **/
        MidiNoteInput(size_u voice, id_u8 channel, tone_d tone, vel_d velocity, bool isPressed);
        CANT_NODISCARD  MidiNoteInput& operator=(const MidiNoteInput&);

        void raiseFlagChangedPlaying();
        void raiseFlagChangedNote();
        void discardAllChangeFlags();

        /** -- fields -- **/
        bool _isPressed;
        bool _flagChangedPlaying;
        bool _flagChangedTone;
    };


    class MidiNoteInternal : public MidiNote<MidiNoteInternalData>, MidiNoteInternalCompatible
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteInternal(size_u voice);

        void set(const MidiNoteInput& input);

        CANT_NODISCARD time_d getLength(time_d tCurrent) const override;

        void setPlaying(bool isPlaying);
        void setChangedPlaying(bool justChanged);
        void setChangedTone(bool justChanged);

        void setTone(tone_d tone) override;
        void setVelocity(vel_d velocity) override;
        void setPan(pan_d pan) override;

        CANT_NODISCARD pan_d getPan() const override;

        CANT_NODISCARD bool isPlaying() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;

    private:
        /** -- fields -- **/
        bool m_isPlaying;
        bool m_justChangedPlaying;
        bool m_justChangedTone;


    };

    class MidiNoteOutput : public MidiNote<MidiNoteOutputData>, MidiNoteOutputCompatible
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteOutput(size_u voice);

        void set(const MidiNoteInternal& internal);

        CANT_NODISCARD time_d getLength(time_d tCurrent) const override;

        CANT_NODISCARD vel_d getVelocityPlaying() const override;
        CANT_NODISCARD Array<vel_d, 2> getVelocityPanned() const override;

        CANT_NODISCARD pan_d getPan() const override;

        CANT_NODISCARD bool isPlaying() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;
        CANT_NODISCARD bool justChangedTone() const override;

        CANT_NODISCARD bool justStarted() const;
        CANT_NODISCARD bool justStopped() const;
    private:
        /** -- methods -- **/
        CANT_NODISCARD vel_d getVelocity() const override;

        /** -- fields -- **/
        bool m_isPlaying;
        bool m_justChangedPlaying;
        bool m_justChangedTone;

    };
}

#include <cant/common/undef_macro.hpp>

#include "MidiNote.inl"

#endif //CANTINA_TILDE_MIDINOTE_HPP
