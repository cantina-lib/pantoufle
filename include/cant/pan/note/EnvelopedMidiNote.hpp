//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_ENVELOPEDMIDINOTE_HPP
#define CANTINA_ENVELOPEDMIDINOTE_HPP

#pragma once

#include <cant/formatting.hpp>

#include <cant/types.hpp>
#include <cant/pan/note/DecoratedMidiNote.hpp>

namespace cant::midi
{
    template<typename T>
    class MidiEnvelope;
    class ToneEnvelope;
    class VelocityEnvelope;
    class MidiEnvelopeLayer;

    class EnvelopedMidiNote final : public DecoratedMidiNote
    {
        template<typename>
        friend class MidiEnvelope;
        friend class ToneEnvelope;
        friend class VelocityEnvelope;
        friend MidiEnvelopeLayer;
    private:
        UPtr<ToneEnvelope> _toneEnv;
        UPtr<VelocityEnvelope> _velEnv;
    private: // unusable here, used by base class
        CANT_NODISCARD UPtr<MidiNote> IMPL_clone() const override;
        CANT_NODISCARD bool justChanged() const override;

        void updateEnvelopes(time_m tCurrent);
        // IMPORTANT: assumes note just changed, hence tStart = tCurrent !!
        void resetEnvelopes();

        CANT_NODISCARD std::string print() const override;

        EnvelopedMidiNote(const EnvelopedMidiNote&);
        EnvelopedMidiNote(const UPtr<ToneEnvelope>& toneEnv, const UPtr<VelocityEnvelope>& velEnv);
        EnvelopedMidiNote(const UPtr<ToneEnvelope>& toneEnv, const UPtr<VelocityEnvelope>& velEnv, const UPtr<MidiNote>& note);
    protected:
        CANT_NODISCARD bool isExtensible() const override { return false; };
        void reset(const UPtr<MidiNote>& note) override;
        void reset() override;
        void update(const UPtr<MidiNote> &) override;


        CANT_NODISCARD bool isSet() const final;
    public:
        /* @brief: updates current note and state. Should be called at every iteration */
        void update(time_m tCurrent) final;
        CANT_NODISCARD bool isPlaying() const override;

        CANT_NODISCARD tone_m getTone() const override;
        CANT_NODISCARD vel_m getVelocity() const override;

        CANT_NODISCARD static UPtr<MidiNote> make(const UPtr<ToneEnvelope>& toneEnv, const UPtr<VelocityEnvelope>& velEnv);

    };


}

#endif //CANTINA_ENVELOPEDMIDINOTE_HPP
