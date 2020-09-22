
#ifndef CANTINA_PAN_ADSRSTATE_INL
#define CANTINA_PAN_ADSRSTATE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN


    CANT_INLINE
    void
    ADSRState::
    setTypeLengthManual(const ADSREnvelope *env, ADSRStateType type)
    {
        setTypeLength(env, type, static_cast<time_d>(0));
    }

    CANT_INLINE
    void
    ADSRState::
    setType(ADSRState::ADSRStateType type)
    {
        const bool wasPlaying = isPlaying();
        m_type = type;
        const bool justChangedPlaying =  wasPlaying != isPlaying();
        if (justChangedPlaying)
        {
            raiseFlagChangedPlaying();
        }
    }


    CANT_INLINE
    void
    ADSRState::
    update(const ADSREnvelope *env, const time_d tDelta)
    {
        compute(env, tDelta);
    }

    CANT_INLINE
    bool
    ADSRState::
    justChangedPlaying() const
    {
        return m_changeFlagModule->justChanged();
    }

    CANT_INLINE
    void
    ADSRState::
    raiseFlagChangedPlaying() const
    {
        return m_changeFlagModule->raiseChangeFlag();
    }


    CANT_INLINE
    type_d
    ADSRState::
    getVelocityRatio() const
    {
        return m_oscillator->operator()();
    }

    CANT_INLINE
    time_d
    ADSRState::
    getLength() const
    {
        return m_length;
    }

    CANT_INLINE
    ADSRState::ADSRStateType
    ADSRState::
    getType() const
    {
        return m_type;
    }



    CANT_INLINE
    bool
    ADSRState::
    isPlaying() const
    {
        return m_type != ADSRStateType::eNotPlaying;
    }

    CANT_INLINE
    bool
    ADSRState::
    isVarying() const
    {
        return isPlaying() && m_type != ADSRStateType::eSustain;
    }


CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PAN_ADSRSTATE_INL