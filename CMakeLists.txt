cmake_minimum_required(VERSION 3.6)

project(pantoufle)


set(PANTOUFLE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(PANTOUFLE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PANTOUFLE_INLINE_DIR ${PROJECT_SOURCE_DIR}/inline)

set(CANTINA_COMMON_DIR ${PROJECT_SOURCE_DIR}/cantina_common)
add_subdirectory(${CANTINA_COMMON_DIR})

set(CMAKE_CXX_STANDARD ${CANTINA_CXX_STANDARD})
set(CMAKE_CXX_FLAGS ${CANTINA_MAIN_CXX_FLAGS})

set(PANTOUFLE_INCLUDE_DIRS
        ${PANTOUFLE_INCLUDE_DIR}
        ${PANTOUFLE_INLINE_DIR}
        ${CANTINA_COMMON_INCLUDE_DIRS}
        CACHE INTERNAL
        "List of include directories for Pantoufle"
        )

include_directories(
        ${PANTOUFLE_INCLUDE_DIRS}
)

set(PANTOUFLE_FILES
        ## source
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/Pantoufle.cpp
        ### note
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/MidiNoteData.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/MidiNoteInput.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/MidiNoteInternalOutput.cpp
        ### io layers
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/layer/MidiNoteInputLayer.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/layer/MidiNoteInternalLayer.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/layer/MidiNoteOutputLayer.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/layer/MidiNoteInputPoly.cpp
        ### env
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/MidiEnvelope.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/ADSREnvelope.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/ADSRState.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/FlatToneEnvelope.cpp
        ### processor
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/processor/MidiControllerChain.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/processor/MidiEnvelopePair.cpp
        ### controller
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiController.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiDamper.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiPan.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiWah.cpp
        ### timer
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/timer/MidiTimer.cpp

        ## headers
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/Pantoufle.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/pan.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/pan_forward.hpp
        ### note
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/note.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/note_forward.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteCompatible.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteData.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteInput.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteInternalOutput.hpp
        ### io layers
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/layer/layer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/layer/MidiNoteLayer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/layer/MidiNoteInputLayer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/layer/MidiNoteInternalLayer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/layer/MidiNoteInputPoly.hpp
        ### env
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/envelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/MidiEnvelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/FlatToneEnvelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/ADSREnvelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/ADSRState.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/adsr_forward.hpp
        ### controller
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/controller.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiController.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MultiMidiController.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiDamper.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiPan.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiWah.hpp
        ### processor
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/processor.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiControllerChain.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiEnvelopePair.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiProcessor.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiProcessorMemory.hpp
        ### control
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/control.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/control_forward.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/MidiControlCompatible.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/MidiControlData.hpp
        ### timer
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/timer/MidiTimer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/timer/TimerUpdate.hpp

        )


add_library(pantoufle STATIC ${PANTOUFLE_FILES})

set(PANTOUFLE_LIBRARIES pantoufle ${CANTINA_COMMON_LIBRARIES} PARENT_SCOPE)

