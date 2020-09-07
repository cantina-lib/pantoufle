//
// Created by binabik on 09/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP
#define CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/note_forward.hpp>
#include <cant/pan/layer/MidiNoteLayer.hpp>

#include <cant/common/macro.hpp>
namespace cant::pan
{
    class MidiNoteInputPoly : public MidiNoteInputLayer
    {
    public:
        /** -- methods -- **/
        CANT_EXPLICIT MidiNoteInputPoly(size_u numberVoices, id_u8 channel);

        void flushChange();

        void receive(time_d tCurrent, const MidiNoteInputData& data) override;
    private:
        /** -- methods -- **/
        CANT_NODISCARD virtual bool chooseVoice(size_u &voice, const MidiNoteInputData &data);

        /** -- fields **/
        id_u8 m_channel;
    };
}
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_MIDINOTEINPUTPOLY_HPP
