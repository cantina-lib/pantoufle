//
// Created by piptouque on 28/04/2020.
//

#ifndef PANTOUFLEENVELOPE_HPP
#define PANTOUFLEENVELOPE_HPP

#pragma once


#include <cant/formatting.hpp>

#include <cant/pan/Time.hpp>

#include <cant/pan/types.hpp>
#include <cant/pan/Cloneable.hpp>

#include <cant/pan/PantoufleException.hpp>

#include <cant/pan/note/EnvelopedMidiNote.hpp>

namespace cant::midi
{

    template <typename T>
    class MidiEnvelope
    {
    private:
        time_m _tCurrent;

    private:
        virtual void IMPL_update(const EnvelopedMidiNote* envNote) = 0;
        virtual void IMPL_reset() = 0;

    protected:

        CANT_NODISCARD time_m getTimeCurrent() const
        {
            return _tCurrent;
        }

        void reset(const time_m tCurrent)
        {
            update(tCurrent);
            IMPL_reset();
        }
    public:
        MidiEnvelope() : _tCurrent() {}
        virtual ~MidiEnvelope() = default;

        void update(time_m tCurrent)
        {
            PANTOUFLE_TRY_RETHROW({
                                         _tCurrent = Time::checkTime(tCurrent);
                                     })
        }

        void update(const EnvelopedMidiNote* envNote, time_m tCurrent)
        {
            update(tCurrent);
            IMPL_update(envNote);
        }

        void reset(const EnvelopedMidiNote* envNote)
        {
            reset(envNote->getStartingTime());
        }

        virtual T operator()(const EnvelopedMidiNote* envNote) const = 0;

    };

    class ToneEnvelope : public MidiEnvelope<tone_m>, private Cloneable<ToneEnvelope>
    {
    protected:
        CANT_NODISCARD UPtr<ToneEnvelope> IMPL_clone() const override = 0;
        CANT_NODISCARD virtual tone_m getToneProcessed(const EnvelopedMidiNote* note) const = 0;
    public:
        CANT_NODISCARD UPtr<ToneEnvelope> clone() const final;
        tone_m operator()(const EnvelopedMidiNote *envNote) const override;

        friend std::ostream& operator<<(std::ostream& out, const VelocityEnvelope* env);
    };


    class VelocityEnvelope : public MidiEnvelope<vel_m>, private Cloneable<VelocityEnvelope>
    {
    private:
        bool _flagChanged;
    private: // called in MidiEnvelope
        void IMPL_reset() final;
        void IMPL_update(const EnvelopedMidiNote* envNote) final;

        virtual void IMPL_Velocity_reset() = 0;
        virtual void IMPL_Velocity_update(const EnvelopedMidiNote* envNote) = 0;
    private:
        void discardFlagChanged();

        CANT_NODISCARD virtual std::string print() const = 0;
    protected:
        VelocityEnvelope();
        VelocityEnvelope(const VelocityEnvelope& velEnv) = default;
        CANT_NODISCARD UPtr<VelocityEnvelope> IMPL_clone() const override = 0;


        CANT_NODISCARD virtual float_m getVelocityRatio() const = 0;
        CANT_NODISCARD virtual bool isEnvelopePlaying() const = 0;
        void raiseFlagChanged();
    public:
        CANT_NODISCARD UPtr<VelocityEnvelope> clone() const final;
        vel_m operator()(const EnvelopedMidiNote* envNote) const final;

        CANT_NODISCARD bool isPlaying(const EnvelopedMidiNote* envNote) const;
        CANT_NODISCARD bool justChanged(const EnvelopedMidiNote* envNote) const;

        friend std::ostream& operator<<(std::ostream& out, const VelocityEnvelope* env);
    };

    std::ostream& operator<<(std::ostream& out, const ToneEnvelope* env);
    std::ostream& operator<<(std::ostream& out, const UPtr<ToneEnvelope>& env);

    std::ostream& operator<<(std::ostream& out, const VelocityEnvelope* env);
    std::ostream& operator<<(std::ostream& out, const UPtr<VelocityEnvelope>& env);

}

#endif //PANTOUFLEENVELOPE_HPP
