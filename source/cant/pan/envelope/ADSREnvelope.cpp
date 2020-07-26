//
// Created by binabik on 30/05/2020.
//

#include <cant/pan/envelope/ADSREnvelope.hpp>

#include <sstream>
#include <fmt/format.h>

namespace cant::midi
{
    UPtr<VelocityEnvelope>
    ADSREnvelope::
    make(const ADSREnvelope::ArrayLength &lengths, const ADSREnvelope::ArrayVelocityRatios &velocities)
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(lengths, velocities));
    }

    ADSREnvelope::
    ADSREnvelope(const ArrayLength& lengths, const ArrayVelocityRatios& velocities)
            : _lengths(lengths),
            _velocities(velocities),
            _type(ADSRStateType::eNotPlaying),
            _tTypeStart()
    {
        checkLengths(lengths);
        setCallbacks();
    }

    UPtr<VelocityEnvelope>
    ADSREnvelope::
    IMPL_clone() const
    {
        return UPtr<VelocityEnvelope>(new ADSREnvelope(*this));
    }


    bool
    ADSREnvelope::
    isEnvelopePlaying() const
    {
        return _type != ADSRStateType::eNotPlaying;
    }



    void
    ADSREnvelope::
    IMPL_Velocity_reset()
    {
        setType(ADSRStateType::eAttack);
    }

    void
    ADSREnvelope::
    checkLengths(const ArrayLength &lengths)
    {
        if (
                (lengths.at(eAttack) < static_cast<time_m>(0.))
                ||(lengths.at(eDecay) < static_cast<time_m>(0.))
                || (lengths.at(eRelease) < static_cast<time_m>(0.))
                )
        {
            /* todo: better message */
            throw PANTOUFLE_EXCEPTION("ADSR length invalid, is negative but not sustain.");
        }
    }

    vel_m
    ADSREnvelope::
    getBarycentre(const time_m lambda, const vel_m v1, const vel_m v2)
    {
        if(lambda > static_cast<time_m>(1.) || lambda < static_cast<time_m>(0.))
        {
            throw PANTOUFLE_EXCEPTION("Lambda out of range.");
        }
        return (static_cast<time_m>(1.) - lambda) * v1 + lambda * v2;
    }

    void
    ADSREnvelope::
    setCallbacks()
    {
        _callbacks.at(eAttack) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eAttack), static_cast<float_m>(0), _velocities.at(eAttack));
                };
        _callbacks.at(eDecay) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eDecay), _velocities.at(eAttack), _velocities.at(eSustain));
                };
        _callbacks.at(eSustain) =
                [this](const time_m t) -> float_m
                {
                    return _velocities.at(eSustain);
                };
        _callbacks.at(eRelease) =
                [this](const time_m t) -> float_m
                {
                    return getBarycentre(t / _lengths.at(eRelease), _velocities.at(eSustain), static_cast<float_m>(0.));
                };
    }

    void
    ADSREnvelope::
    IMPL_Velocity_update(const EnvelopedMidiNote* envNote)
    {
        updateType(envNote);
    }

    time_m
    ADSREnvelope::
    getTypeLength() const
    {
        time_m typLength;
        PANTOUFLE_TRY_RETHROW({
             typLength = Time::checkTime(getTimeCurrent() - _tTypeStart);
        })
        return typLength;
    }

    void
    ADSREnvelope::
    updateType(const EnvelopedMidiNote* envNote)
    {
        if(envNote->hasBaseJustStarted())
        {
            setType(ADSRStateType::eAttack);
        }
        else if(envNote->hasBaseJustStopped())
        {
            setType(ADSRStateType::eRelease);
        }
        else
        {
            ADSRStateType type = _type;
            time_m typeLength = getTypeLength();
            REC_updateType(type, typeLength);
            if(type != _type)
            {
                setType(type, typeLength);
            }
        }
    }

    void
    ADSREnvelope::
    setType(const ADSRStateType type)
    {
        setType(type, static_cast<time_m>(0.));
    }

    void
    ADSREnvelope::
    setType(const ADSRStateType type, const time_m typeLength)
    {
        if(type == ADSRStateType::eAttack || type == ADSRStateType::eNotPlaying)
        {
            raiseFlagChanged();
        }
        _type = type;
        PANTOUFLE_TRY_RETHROW({
             _tTypeStart = Time::checkTime(getTimeCurrent() - typeLength);
        })
    }

    void
    ADSREnvelope::
    REC_updateType(ADSRStateType& type, time_m& typeLength) const
    {
        switch (type)
        {
            case ADSRStateType::eAttack:
                if (typeLength > _lengths.at(eAttack))
                {
                    /* */
                    type = ADSRStateType::eDecay;
                    typeLength -= _lengths.at(eAttack);
                    break;
                }
                return;
            case ADSRStateType::eDecay:
                if (typeLength > _lengths.at(eDecay))
                {
                    type = ADSRStateType::eSustain;
                    typeLength -= _lengths.at(eDecay);
                    break;
                }
                return;
            case ADSRStateType::eSustain:
                if (isSustainFinite() && (typeLength >  _lengths.at(eSustain)))
                {
                    type = ADSRStateType::eRelease;
                    typeLength -= _lengths.at(eSustain);
                    break;
                }
                return;
            case ADSRStateType::eRelease:
                if (typeLength > _lengths.at(eRelease))
                {
                    type = ADSRStateType::eNotPlaying;
                    typeLength -= _lengths.at(eRelease);
                    break;
                }
                return;
            case ADSRStateType::eNotPlaying:
                /* nothing to do */
                return;
        }
        REC_updateType(type, typeLength);
    }

    bool
    ADSREnvelope::
    isSustainFinite() const
    {
        return _lengths.at(eSustain) >= static_cast<time_m>(0.);
    }

    float_m
    ADSREnvelope::
    getVelocityRatio() const
    {
        if(!isEnvelopePlaying())
        {
            return static_cast<vel_m>(0.);
        }
        return _callbacks.at(_type)(getTypeLength());
    }

    std::string
    ADSREnvelope::
    print() const
    {
        std::stringstream stream;
        stream << "[adsr] { ";
        stream << ADSR_STATYPE_NAMES[_type] << fmt::format("[{0}, {1}]", getTypeLength(), getVelocityRatio());
        stream << " }";
        return stream.str();
    }
}

