
#ifndef CANTINA_PAN_MIDINOTEINPUT_HPP
#define CANTINA_PAN_MIDINOTEINPUT_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/pan/timer/ChangeFlagUpdatable.hpp>
#include <cant/pan/timer/TimeUpdatable.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiTimer;

    class MidiNoteInput :
            public MidiNote<MidiNoteInputData>,
            public MidiNoteInputCompatible,
            public event::Listener<MidiTimer>
    {
    public:
        /** -- structs -- **/
        class ChangeFlagUpdateModule : public ChangeFlagUpdatable
        {
        private:
            /** -- friends -- **/
            friend class MidiNoteInput;
        };

        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteInput(size_u voice);

        void set(time_d tCurrent, const MidiNoteInputData& data);


        CANT_NODISCARD bool isPlaying() const override;
        CANT_NODISCARD bool justChangedPlaying() const override;

        CANT_NODISCARD tone_i8 getToneNative() const;
        CANT_NODISCARD vel_i8  getVelocityNative() const;

        // Implemntation of ListenerInterface
        void subscribe(event::Ptr<MidiTimer> timer) override;
        void unsubscribe(event::Ptr<MidiTimer> timer) override;

    private:
        /** -- methods -- **/

        /** -- fields -- **/
        UPtr<ChangeFlagUpdateModule> m_changeFlagUpdateModule;
        bool m_isPressed;
    };

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/note/MidiNoteInput.inl>

#endif //CANTINA_PAN_MIDINOTEINPUT_HPP