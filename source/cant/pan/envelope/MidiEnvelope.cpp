//
// Created by piptouque on 30/04/2020.
//
#include <cant/pan/envelope/MidiEnvelope.hpp>

#include <cant/pan/note/MidiNoteInternalOutput.hpp>

#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    MidiEnvelopeWrapper::TimeUpdateModule::
    TimeUpdateModule(UPtr<cant::pan::MidiEnvelope> a_envModule)
    : env(std::move(a_envModule))
    {

    }

    void
    MidiEnvelopeWrapper::TimeUpdateModule::
    updateDelta(time_d tDelta)
    {
        env->updateDelta(tDelta);
    }

    MidiEnvelope::
    MidiEnvelope() = default;

    MidiEnvelopeWrapper::
    MidiEnvelopeWrapper(UPtr<cant::pan::MidiEnvelope> envModule)
        : m_timeUpdateModule(std::make_unique<TimeUpdateModule>(std::move(envModule)))
    {

    }

    void
    MidiEnvelopeWrapper::
    subscribe(event::Ptr<MidiTimer> timer)
    {
        m_timeUpdateModule->subscribe(timer->timeModule.get());
        m_timeUpdateModule->env->subscribe(timer);

    }

    void
    MidiEnvelopeWrapper::
    unsubscribe(event::Ptr<MidiTimer> timer)
    {
         m_timeUpdateModule->env->unsubscribe(timer);
        m_timeUpdateModule->unsubscribe(timer->timeModule.get());
    }

    void
    MidiEnvelopeWrapper::
    process(MidiNoteInternal &note)
    {
        m_timeUpdateModule->env->process(note);
    }



CANTINA_PAN_NAMESPACE_END







