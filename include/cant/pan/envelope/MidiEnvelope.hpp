//
// Created by piptouque on 28/04/2020.
//

#ifndef CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
#define CANTINA_PANTOUFLE_MIDIENVELOPE_HPP

#pragma once


#include <cant/pan/common/types.hpp>

#include <cant/pan/processor/MidiProcessor.hpp>

#include <cant/pan/timer/MidiTimer.hpp>
#include <cant/pan/timer/TimeUpdatable.hpp>


#include <cant/common/macro.hpp>
CANTINA_PAN_NAMESPACE_BEGIN

    class MidiEnvelope
            : public MidiProcessor,
              public event::Listener<MidiTimer>
    {
    public:
        /** -- methods -- **/
        MidiEnvelope();
        // optional implementation of Listener interface
        // Is used by ADSR envelope (actually each states thereof)
        void subscribe  (CANT_MAYBEUNUSED event::Ptr<MidiTimer> timer) override { }
        void unsubscribe(CANT_MAYBEUNUSED event::Ptr<MidiTimer> timer) override { }

        // managed by MidiEnvelopeTrait
        virtual void updateDelta(time_d tDelta) = 0;

        void process(MidiNoteInternal& note) override = 0;
    };


    class ToneEnvelope : public MidiEnvelope
    {
    public:
        /** -- methods -- **/
        void process(MidiNoteInternal& note) override = 0;
    };



    class VelocityEnvelope : public MidiEnvelope
    {
    public:
        /** -- methods -- **/
        void process(MidiNoteInternal& note) override = 0;
    };


    class MidiEnvelopeWrapper : public MidiProcessor, public event::Listener<MidiTimer>
    {
    public:
        /** -- structs -- **/
        class TimeUpdateModule : public DeltaTimeUpdatable
        {
        public:
            /** -- methods -- **/
            CANT_EXPLICIT TimeUpdateModule(UPtr<MidiEnvelope> envModule);

            void updateDelta(time_d tDelta) override;

            /** -- fields -- **/
            UPtr<MidiEnvelope> env;
        };

        /** -- methods -- **/
        CANT_EXPLICIT MidiEnvelopeWrapper(UPtr<MidiEnvelope> envMod);

        // implementation of MidiEnvelope
        void process(MidiNoteInternal& note) override;

        // implementation of Listener interface
        void subscribe(event::Ptr<MidiTimer> timer) override;
        void unsubscribe(event::Ptr<MidiTimer> timer) override;

    private:
        /** -- fields -- **/
        UPtr<TimeUpdateModule> m_timeUpdateModule;
    };




CANTINA_PAN_NAMESPACE_END
#include <cant/common/undef_macro.hpp>

#endif //CANTINA_PANTOUFLE_MIDIENVELOPE_HPP
