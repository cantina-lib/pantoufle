//
// Created by binabik on 21/09/2020.
//

#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiNoteInput::
    MidiNoteInput(const size_u voice)
            : MidiNote<MidiNoteInputData>(voice),
              m_changeFlagUpdateModule(std::make_unique<ChangeFlagUpdateModule>()),
              m_isPressed(false)
    { }


    void
    MidiNoteInput::
    set(const time_d tCurrent, const MidiNoteInputData &data)
    {
        const bool wasPlaying = isPlaying();

        m_isPressed = data.isPressed();

        if (data.isPressed())
        {
            if (!wasPlaying)
            {
                // a note is born!
                m_tStart = tCurrent;
            }
            m_data = data;
        }
        if (isPlaying() != wasPlaying)
        {
            m_changeFlagUpdateModule->raiseChangeFlag();
        }
    }

    void
    MidiNoteInput::
    subscribe(event::Ptr <MidiTimer> timer)
    {
        m_changeFlagUpdateModule->subscribe(timer->changeFlagModule.get());
    }

    void
    MidiNoteInput::
    unsubscribe(event::Ptr <MidiTimer> timer)
    {
        m_changeFlagUpdateModule->unsubscribe(timer->changeFlagModule.get());
    }


CANTINA_PAN_NAMESPACE_END
