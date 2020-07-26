//
// Created by binabik on 30/05/2020.
//

#ifndef CANTINA_FLATENVELOPE_HPP
#define CANTINA_FLATENVELOPE_HPP

#pragma once

#include <cant/pan/envelope/MidiEnvelope.hpp>

namespace cant::midi
{
    class FlatToneEnvelope final : protected ToneEnvelope
    {
    private:
        FlatToneEnvelope() = default;
    private: // private inheritance, called in MidiEnvelope
        void IMPL_update(const EnvelopedMidiNote* note) override;
        void IMPL_reset() override;
    protected:
        CANT_NODISCARD UPtr<ToneEnvelope> IMPL_clone() const override;
        CANT_NODISCARD tone_m getToneProcessed(const EnvelopedMidiNote* note) const override;
    public:

        static UPtr<ToneEnvelope> make();
    };
}


#endif //CANTINA_FLATENVELOPE_HPP
