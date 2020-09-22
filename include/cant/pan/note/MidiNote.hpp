//
// Created by binabik on 01/08/2020.
//

#ifndef CANTINA_TILDE_MIDINOTEINTERNALOUTPUT_HPP
#define CANTINA_TILDE_MIDINOTEINTERNALOUTPUT_HPP

#pragma once

#include <cant/pan/common/types.hpp>

#include <cant/pan/note/MidiNoteCompatible.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    template <typename Data_T>
    class MidiNote : MidiNoteCompatible
    {
    public:
        /** -- methods -- **/
        /*
         * todo: get undefined symbol when defining abstract destructor here
         * probably has to do with template, when instantiating it... whatever,
         * it'll have to be concrete.
         */
        CANT_EXPLICIT MidiNote(size_u voice);

        MidiNote(const MidiNote&);
        MidiNote& operator=(const MidiNote&);

        CANT_NODISCARD const Data_T& getData() const;
        CANT_NODISCARD size_u getVoice() const;

        CANT_NODISCARD id_u8 getChannel() const override;
        CANT_NODISCARD tone_d getTone() const override;
        CANT_NODISCARD vel_d getVelocity() const override;

        CANT_NODISCARD time_d getStartingTime() const override;
    protected:
        /** -- fields -- **/
        Data_T m_data;
        size_u m_voice;
        time_d m_tStart;
    };




CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#include <cant/pan/note/MidiNote.inl>

#endif //CANTINA_TILDE_MIDINOTEINTERNALOUTPUT_HPP
