//
// Created by binabik on 09/08/2020.
//

#include <cant/pan/layer/MidiNoteInputPoly.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiNoteInputPoly::
    MidiNoteInputPoly(size_u numberVoices, id_u8 channel)
    : MidiNoteInputLayer(numberVoices),
      m_channel(channel)
    {

    }

    void
    MidiNoteInputPoly::
    flushChange()
    {
        for(auto& note : m_notes)
        {
            note.flushChange();
        }
    }

    Optional<size_u>
    MidiNoteInputPoly::
    receive(const time_d tCurrent, const MidiNoteInputData &data)
    {
        /*
         * in this case, there is no getVoice(),
         * we have to choose it instead.
         */
        Optional<size_u> optVoice = chooseVoice(data);
        if (optVoice)
        {
            m_notes.at(optVoice.value()).set(tCurrent, data);
        }
        return optVoice;
    }

    CANT_CONSTEXPR
    static auto
    findClosestToneIndex = [](
            const Stream<MidiNoteInput>& notes,
            const MidiNoteInputData& inputData,
            bool force) -> Optional<size_u>
    {
        tone_i8 closestDist = c_midiMaxTone;
        bool foundClosest = false;
        size_u closestIndex = 0;
        size_u i = 0;
        for (const auto& note : notes)
        {
            if (!note.isPlaying() || force)
            {
                const auto dist = static_cast<tone_i8>(
                        static_cast<cant::type_i>(note.getToneNative())
                        - static_cast<cant::type_i>(inputData.getToneNative())
                );
                if (!foundClosest || dist < closestDist)
                {
                    closestDist = dist;
                    closestIndex = i;
                    foundClosest = true;
                }
            }
            ++i;
        }
        return foundClosest ? Optional<size_u>(closestIndex) : std::nullopt;
    };

    Optional <size_u>
    MidiNoteInputPoly::
    chooseVoice(const MidiNoteInputData &data)
    {
        const bool inputIsPressed = data.isPressed();
        const tone_i8 inputTone = data.getToneNative();

        /*
         * The way it works in Pure Data when a note is received by the poly object is:
         * - if it stopped being pressed (vel = 0) then we choose the voice with the note's tone.
         * - if it started:
         * -- voice stealing -> we take next voice to the last voice we updated, regardless of whether it is pressed.
         * -- no stealing -> take next voice which is not playing. If all notes are playing, no note is updated.
         */
        /*
         * We could go for a mix of both. I think favouring stealing a note with the same tone.
         * -- If not, steal the note with the tone that's closest to input.
         * -- Mainly so that it disorients as little as possible the pitch-shifter it is assigned to.
         * Another difference is that we won't allow multiple notes with the same tone.
         */
        /*
         * Remember that tone, velocity can be compared because they are represented
         * by integer in InputData, but then go to floating-point in InternalData
         */
        {
            size_u i = 0;
            for (const auto& note : m_notes)
            {
                const bool noteIsSame = note.getToneNative() == inputTone;
                if (noteIsSame)
                {
                    return Optional<size_u>(i);
                }
                ++i;
            }
        }
        // Second pass, taking ownership of note with closest tone.
        if (auto optVoice = findClosestToneIndex(m_notes, data, false))
        {
            return optVoice;
        }
        /*
         * by this time, if input is not pressed and there was no note to signal,
         * we simply return without changing anything.
         */
        if (!inputIsPressed)
        {
            return std::nullopt;
        }
        /* forced pass -> stealing */
        return findClosestToneIndex(m_notes, data, true);
    }

CANTINA_PAN_NAMESPACE_END
