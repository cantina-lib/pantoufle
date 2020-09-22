//
// Created by binabik on 05/06/2020.
//

#include <cant/pan/controller/MidiDamper.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiDamper::
    MidiDamper(const size_u numberVoices, const id_u8 channel, const id_u8 controllerId)
    : MultiMidiController<1>(numberVoices, channel, { controllerId }),
      m_shouldHoldNotes(numberVoices, false),
      m_isMemoryPlaying(numberVoices, false)
    {

    }

    bool
    MidiDamper::
    isOn() const
    {
          return isOn(getControl(0));
    }

    bool
    MidiDamper::
    isOn(const MidiControlInternal &control)
    {
        return control.getValue() > c_midiControlMidValue;
    }

    void
    MidiDamper::
    beforeControlProcess(const MidiControlInternal& incomingControl)
    {
        /*
         * Control is not yet updated,
         * so we compare with the incoming control.
         */
        for (auto& shouldHold : m_shouldHoldNotes)
        {
            shouldHold = static_cast<id_u8>(
                    static_cast<bool>(shouldHold)
                    && isOn(incomingControl)
                    );
        }
    }

    void
    MidiDamper::
    beforeNoteProcess(const MidiNoteInternal& incomingNote)
    {
        const size_u voice = incomingNote.getVoice();
        m_isMemoryPlaying.at(voice) = getMemory(voice).isPlaying();
        m_shouldHoldNotes.at(voice) = static_cast<id_u8>(
                isOn()
                && (static_cast<bool>(m_isMemoryPlaying.at(voice)) || incomingNote.isPlaying())
                );
    }

    void
    MidiDamper::
    IMPL_process(MidiNoteInternal &note) const
    {
        const size_u voice = note.getVoice();
        const bool shouldHold = static_cast<bool>(m_shouldHoldNotes.at(voice));
        note.setPlaying(note.isPlaying() || shouldHold);
        /*
         * After setting the playing state to it
         * the note can be compared to the last processed one (memory)
         * to decide whether it has changed.
         * It's pretty overkill, but it gets the work done.
         */
        note.setChangedPlaying(
                note.isPlaying()
                != static_cast<bool>(m_isMemoryPlaying.at(voice))
                );
    }

    UPtr<MidiController>
    MidiDamper::
    make(const size_u numberVoices, const id_u8 channel, const id_u8 controllerId)
    {
        return UPtr<MidiController>(new MidiDamper(numberVoices, channel, controllerId));
    }

CANTINA_PAN_NAMESPACE_END