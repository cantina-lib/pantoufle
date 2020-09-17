//
// Created by binabik on 15/09/2020.
//

#ifndef CANTINA_TILDE_PANTOUFLE_INL
#define CANTINA_TILDE_PANTOUFLE_INL

#include <cant/pan/time/MidiTimer.hpp>
#include <cant/pan/layer/MidiNoteInputPoly.hpp>
#include <cant/pan/layer/MidiNoteLayer.hpp>
#include <cant/pan/processor/MidiEnvelopePair.hpp>
#include <cant/pan/processor/MidiControllerChain.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    CANT_INLINE
    void
    Pantoufle::
    update()
    {
        updateTimer();
        const time_d tCurrent = getCurrentTime();
        updateControlChain(tCurrent);
        updateEnvelopeLayer(tCurrent);
        processAll();
        flushChange();
    }

    CANT_INLINE
    void
    Pantoufle::
    processAll()
    {
        /*
         * Whatever the case, we will have to process the notes
         * each time we update, so no need to process them individually
         * when they are received.
         */
        for (size_u i = 0; i < getNumberVoices(); ++i)
        {
            process(i);
        }

    }

    CANT_INLINE
    const Stream<MidiNoteOutput>&
    Pantoufle::
    getProcessedNoteOutput() const
    {
        return m_processedNoteOutput->getNotes();
    }

    CANT_INLINE
    const MidiNoteOutput&
    Pantoufle::
    getProcessedVoice(size_u voice) const
    {
        return m_processedNoteOutput->getVoice(voice);
    }

    CANT_INLINE
    void
    Pantoufle::
    flushChange()
    {
        flushChangeNoteInput();
        flushChangeEnvelopePair();
    }

    CANT_INLINE
    void
    Pantoufle::
    flushChangeNoteInput()
    {
        m_poly->flushChange();
    }

    CANT_INLINE
    void
    Pantoufle::
    flushChangeEnvelopePair()
    {
        m_envelopePair->flushChange();
    }

    CANT_INLINE
    void
    Pantoufle::
    updateControlChain(const time_d tCurrent)
    {
        m_controllerChain->update(tCurrent);
    }

    CANT_INLINE
    void
    Pantoufle::
    updateEnvelopeLayer(const time_d tCurrent)
    {
        m_envelopePair->update(tCurrent);
    }

    CANT_INLINE
    void
    Pantoufle::
    updateTimer()
    {
        m_timer->update();
    }


    CANT_INLINE
    time_d
    Pantoufle::
    getCurrentTime() const
    {
        return m_timer->getCurrentTime();
    }

    CANT_INLINE
    size_u
    Pantoufle::
    getNumberVoices() const
    {
        return m_poly->getNumberVoices();
    }

    CANT_INLINE
    void
    Pantoufle::
    processControllerChainVoice(const size_u voice)
    {
        m_controllerChain->process(m_processedNoteInternal->getVoiceMutable(voice));
    }

    CANT_INLINE
    void
    Pantoufle::
    processEnvelopePairVoice(const size_u voice)
    {
        m_envelopePair->process(m_processedNoteInternal->getVoiceMutable(voice));
    }

    CANT_INLINE
    void
    Pantoufle::
    receiveRawControlData(const MidiControlInputData &controlData)
    {
        const auto control = MidiControlInternal(controlData);
        m_controllerChain->receiveControl(control);
    }

CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_TILDE_PANTOUFLE_INL
