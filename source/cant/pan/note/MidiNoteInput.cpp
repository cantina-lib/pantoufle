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
              m_isPressed(false),
      m_justChangedPlaying(false),
      m_tickListener()
    {
      m_tickListener =
          std::make_shared<patterns::SelfEventListener<MidiNoteInput, void*>>(
              this,
              &MidiNoteInput::onTimerTick
          );
    }


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
          m_justChangedPlaying = true;
        }
    }

    void
    MidiNoteInput::
    subscribe(UPtr <MidiTimer>& timer)
    {
        timer->addOnTickListener(m_tickListener);
    }

    void
    MidiNoteInput::
    unsubscribe(UPtr <MidiTimer>& timer)
    {
        timer->removeOnTickListener(m_tickListener);
    }

    void
    MidiNoteInput::onTimerTick(void *)
    {
      // reset flag changed!
            m_justChangedPlaying = false;
    }


    CANTINA_PAN_NAMESPACE_END
