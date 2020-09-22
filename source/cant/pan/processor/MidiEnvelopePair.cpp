//
// Created by piptouque on 28/04/2020.
//

#include <cant/pan/processor/MidiEnvelopePair.hpp>

#include <cant/pan/timer/MidiTimer.hpp>

#include <cant/pan/envelope/envelope.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiEnvelopePair::
    MidiEnvelopePair
    (
            size_u numberVoices,
            id_u8 channel,
            const UPtr <MidiTimer> &timer
    )
    : m_toneEnvelopeWrapper(std::make_unique<MidiEnvelopeWrapper>(FlatToneEnvelope::make())),
      m_velocityEnvelopeWrapper(std::make_unique<MidiEnvelopeWrapper>(ADSREnvelope::make(numberVoices))),
      m_channel(channel)
    {
        m_toneEnvelopeWrapper->subscribe(timer.get());
        m_velocityEnvelopeWrapper->subscribe(timer.get());
    }

    void
    MidiEnvelopePair::
    process(MidiNoteInternal& note)
    {
        m_toneEnvelopeWrapper->process(note);
        m_velocityEnvelopeWrapper->process(note);
    }

CANTINA_PAN_NAMESPACE_END
