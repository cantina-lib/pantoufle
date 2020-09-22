
#ifndef CANTINA_PAN_MIDINOTEINPUTLAYER_HPP
#define CANTINA_PAN_MIDINOTEINPUTLAYER_HPP

#pragma once

#include <cant/common/option.hpp>

#include <cant/pan/layer/MidiNoteLayer.hpp>
#include <cant/pan/note/MidiNoteInput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiNoteInputLayer : public MidiNoteLayerInterface<MidiNoteInput>
    {
    public:
        /** -- methods  -- **/
        CANT_EXPLICIT MidiNoteInputLayer(size_u numberVoices);

        virtual Optional<size_u> receive(time_d tCurrent, const MidiNoteInputData &data) = 0;

        CANT_NODISCARD const MidiNoteInput& getVoice(size_u voice) const final;

        CANT_NODISCARD size_u getNumberVoices() const final;

    protected:
        /** -- fields -- **/
        Stream<MidiNoteInput> m_inputNotes;
    };

CANTINA_PAN_NAMESPACE_END

#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_MIDINOTEINPUTLAYER_HPP