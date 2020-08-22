//
// Created by binabik on 09/08/2020.
//

#include <cant/pan/layer/MidiNoteInputPoly.hpp>

namespace cant::pan
{
    MidiNoteInputPoly::
    MidiNoteInputPoly(size_m numberVoices, byte_m channel)
    : MidiNoteInputLayer(numberVoices),
    _channel(channel)
    {

    }

    void
    MidiNoteInputPoly::
    flushChange()
    {
        for(auto& note : _notes)
        {
            note.flushChange();
        }
    }

    void MidiNoteInputPoly::
    receive(const time_m tCurrent, const MidiNoteInputData &data)
    {
        /*
         * in this case, there is no getVoice(),
         * we have to choose it instead.
         */
        size_m voice;
        bool isChosen = chooseVoice(voice, data);
        if (isChosen)
        {
            _notes.at(voice).set(tCurrent, data);
        }
    }

    bool
    MidiNoteInputPoly::
    chooseVoice(size_m &voice, const MidiNoteInputData &data)
    {
        const tone_m inputTone = data.getTone();
        const bool inputIsPressed = data.isPressed();

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
        size_m i = 0;
        for (const auto& note : _notes)
        {
            const bool noteIsSame = note.getTone() == inputTone;
            if (noteIsSame)
            {
                voice = i;
                return true;
            }
            ++i;
        }
        // Second pass, taking ownership of note with closest tone.
        auto findClosestToneIndex = [this](const MidiNoteInputData& inputData, size_m& closestIndex, bool force) -> bool
        {
            tone_mint closestDist;
            bool foundClosest = false;
            size_m i = 0;
            for (const auto& note : _notes)
            {
                if (!note.isPressed() || force)
                {
                    const tone_mint dist = std::abs(note.getTone() - inputData.getTone());
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
        if (findClosestToneIndex(data, voice, false))
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
        findClosestToneIndex(data, voice, true);
        return true;
    }
}