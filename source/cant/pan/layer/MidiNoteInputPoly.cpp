//
// Created by binabik on 09/08/2020.
//

#include <cant/pan/layer/MidiNoteInputPoly.hpp>

#include <cant/pan/note/MidiNote.hpp>
#include <cant/pan/note/MidiNoteData.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{

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

    void
    MidiNoteInputPoly::
    receive(const time_d tCurrent, const MidiNoteInputData &data)
    {
        /*
         * in this case, there is no getVoice(),
         * we have to choose it instead.
         */
        size_u voice;
        bool isChosen = chooseVoice(voice, data);
        if (isChosen)
        {
            m_notes.at(voice).set(tCurrent, data);
        }
    }

    CANT_CONSTEXPR
    static auto
    findClosestToneIndex = [](
            const Stream<MidiNoteInput>& notes,
            const MidiNoteInputData& inputData,
            size_u& closestIndex,
            bool force) -> bool
    {
        tone_u8 closestDist;
        bool foundClosest = false;
        size_u i = 0;
        for (const auto& note : notes)
        {
            if (!note.isPressed() || force)
            {
                const tone_u8 dist = std::abs(note.getTone() - inputData.getTone());
                if (!foundClosest || dist < closestDist)
                {
                    closestDist = dist;
                    closestIndex = i;
                    foundClosest = true;
                }
            }
            ++i;
        }
        return foundClosest;
    };

    bool
    MidiNoteInputPoly::
    chooseVoice(size_u &voice, const MidiNoteInputData &data)
    {
        const bool inputIsPressed = data.isPressed();
        const tone_u8 inputTone = data.getTone();

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
                const bool noteIsSame = note.getTone() == inputTone;
                if (noteIsSame)
                {
                    voice = i;
                    return true;
                }
                ++i;
            }
        }
        // Second pass, taking ownership of note with closest tone.
        if (findClosestToneIndex(m_notes, data, voice, false))
        {
            return true;
        }
        /*
         * by this time, if input is not pressed and there was no note to signal,
         * we simply return without changing anything.
         */
        if (!inputIsPressed)
        {
            return false;
        }
        /* forced pass -> stealing */
        findClosestToneIndex(m_notes, data, voice, true);
        return true;
    }
}