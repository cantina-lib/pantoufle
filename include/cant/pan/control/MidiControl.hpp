//
// Created by piptouque on 29/04/2020.
//

#ifndef CANTINA_MIDICONTROL_HPP
#define CANTINA_MIDICONTROL_HPP

#pragma once

#include <cant/common/formatting.hpp>

#include <cant/pan/control/MidiControlData.hpp>

#include <cant/pan/common/types.hpp>
#include <cant/pan/common/Cloneable.hpp>

namespace cant::pan
{

    class MidiControl
    {
    private:
        MidiControlInput _input;
    private:
        CANT_NODISCARD static bool isControlSet(const MidiControl* control);


        CANT_EXPLICIT MidiControl(const MidiControlInput& input);
        MidiControl() = default;
        MidiControl(const MidiControl&) = default;

    public:

        CANT_NODISCARD static bool isControlSet(const ShPtr<MidiControl>& control);
        /* should only be call by MidiController */
        CANT_NODISCARD static ShPtr<MidiControl> makeShared();

        static void set(WPtr<MidiControl>& dest, const ShPtr<MidiControl>& src);
        static void reset(WPtr<MidiControl>& dest);

        static void update(ShPtr<MidiControl>& control, const MidiControlInput& input);

        CANT_NODISCARD byte_m getControllerId() const;
        CANT_NODISCARD byte_m getValue() const;



        friend std::ostream& operator<<(std::ostream& out, const MidiControl* control);
    };

    /*
     * note to self:
     * if there's a type mismatch between a declaration of operator<< with std::shared_ptr
     * and a definition of operator<< with std::unique_ptr,
     * at the execution it will just get you an undecipherable mangled name
     * and waste an entire afternoon of your time.
     *      sincerely yours,
     *                  you
     */
    std::ostream& operator<<(std::ostream& out, const ShPtr<MidiControl>& control);
}

#endif //CANTINA_MIDICONTROL_HPP
