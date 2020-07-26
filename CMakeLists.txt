cmake_minimum_required(VERSION 3.6)

project(pantoufle)


set(PANTOUFLE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)
set(PANTOUFLE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)


set(CMAKE_CXX_STANDARD 20)

set(CANTINA_COMMON_DIR ${PROJECT_SOURCE_DIR}/cantina_common)

add_subdirectory(${CANTINA_COMMON_DIR})

include_directories(
        ${PANTOUFLE_INCLUDE_DIR}
        ${CANTINA_COMMON_DIR}/include
)

# flags
set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC")


set(PANTOUFLE_FILES
        ## source
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/Pantoufle.cpp
        ### note
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/MidiNoteData.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/MidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/RawMidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/DecoratedMidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/LazyMidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/EnvelopedMidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/ControlledMidiNote.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/note/DampMidiNote.cpp
        ### env
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/MidiEnvelope.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/ADSREnvelope.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/envelope/FlatEnvelope.cpp
        ### control
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/control/MidiControl.cpp
        ### processor
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/processor/MidiControllerChain.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/processor/MidiEnvelopeLayer.cpp
        ### controller
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiController.cpp
        ${PANTOUFLE_SOURCE_DIR}/cant/pan/controller/MidiDamper.cpp


        ## headers
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/Pantoufle.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/pan.hpp
        ### env
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/envelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/MidiEnvelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/FlatEnvelope.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/envelope/ADSREnvelope.hpp
        ### controller
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/controller.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiController.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/controller/MidiDamper.hpp
        ### processor
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/processor.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiControllerChain.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiEnvelopeLayer.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/processor/MidiProcessor.hpp
        ### control
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/control.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/MidiControlCompatible.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/MidiControl.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/control/MidiControlData.hpp
        ### stream
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/stream/MidiStream.hpp
        ### note
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/note.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteCompatible.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/MidiNoteData.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/RawMidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/DecoratedMidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/LazyMidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/EnvelopedMidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/ControlledMidiNote.hpp
        ${PANTOUFLE_INCLUDE_DIR}/cant/pan/note/DampMidiNote.hpp )


add_library(pantoufle ${PANTOUFLE_FILES})

target_link_libraries(pantoufle cantina_common)

