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
        MidiNote(size_m voice, byte_m channel, tone_m tone, vel_m velocity)
        : _data(channel, tone, velocity), _voice(voice), _tStart()
        {

        }

        CANT_EXPLICIT MidiNote(size_m voice)
        : _data(),  _voice(voice), _tStart()
        {

        }

        CANT_NODISCARD const Data_T& getData() const { return _data; }

        CANT_NODISCARD size_m getVoice() const { return _voice; }

        CANT_NODISCARD byte_m getChannel() const override { return _data.getChannel(); }
        CANT_NODISCARD tone_m getTone() const override    { return _data.getTone(); }
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

        CANT_NODISCARD time_m getStartingTime() const override { return _tStart; }
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

        CANT_NODISCARD bool isPressed() const override   { return _isPressed; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _flagChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _flagChangedTone; }
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

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        void setPlaying(bool isPlaying) { _isPlaying = isPlaying; }
        void setChangedPlaying(const bool justChanged) { _justChangedPlaying = justChanged; }
        void setChangedTone(const bool justChanged) { _justChangedTone = justChanged; }

        void setTone(const tone_m tone) override { _data.setTone(tone); }
        void setVelocity(const vel_m velocity) override { _data.setVelocity(velocity); }
        void setPan(const pan_m pan) override { _data.setPan(pan); }

        CANT_NODISCARD pan_m getPan() const override { return _data.getPan(); }

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _justChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _justChangedTone; }

    };

    class MidiNoteOutput : public MidiNote<MidiNoteOutputData>, MidiNoteOutputCompatible
    {
    private:
        bool _isPlaying;
        bool _justChangedPlaying;
        bool _justChangedTone;
    private:
        CANT_NODISCARD vel_m getVelocity() const override { return _data.getVelocity(); }

    public:
        CANT_EXPLICIT MidiNoteOutput(size_m voice);

        void set(const MidiNoteInternal& internal);

        CANT_NODISCARD time_m getLength(const time_m tCurrent) const override { return tCurrent - _tStart; }

        CANT_NODISCARD vel_m getVelocityPlaying() const override;
        CANT_NODISCARD Array<vel_m, 2> getVelocityPanned() const override { return _data.getVelocityPanned(); }

        CANT_NODISCARD pan_m getPan() const override { return _data.getPan(); }

        CANT_NODISCARD bool isPlaying() const override   { return _isPlaying; }
        CANT_NODISCARD bool justChangedPlaying() const override { return _justChangedPlaying; }
        CANT_NODISCARD bool justChangedTone() const override { return _justChangedTone; }

        CANT_NODISCARD bool justStarted() const { return _justChangedPlaying && isPlaying(); }
        CANT_NODISCARD bool justStopped() const { return _justChangedPlaying && !isPlaying(); }

    };
}

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_MIDINOTE_HPP
