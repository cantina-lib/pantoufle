
#ifndef CANTINA_PAN_ADSRSTATE_INL
#define CANTINA_PAN_ADSRSTATE_INL

#pragma once

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN



    CANT_INLINE
    void
    ADSRState::
    setType(const ADSREnvelope* env, ADSRState::ADSRStateType type)
    {
        const bool wasPlaying = isPlaying();
        const bool justChanged = type != m_type;
        const bool justChangedPlaying =  wasPlaying != isPlaying();

        m_type = type;

        if (justChangedPlaying)
        {
            raiseFlagChangedPlaying();
        }
        if (justChanged)
        {
            resetTarget(env);
        }
    }


    CANT_INLINE
    bool
    ADSRState::
    justChangedPlaying() const
    {
      return m_flagJustChangedPlaying;
    }

    CANT_INLINE
    void
    ADSRState::
    raiseFlagChangedPlaying()
    {
      m_flagJustChangedPlaying = true;
    }


    CANT_INLINE
    type_d
    ADSRState::
    getVelocityRatio() const
    {
        return m_object->getPosition().get<0>();
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