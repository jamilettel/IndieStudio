/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Preset
*/

#ifndef PRESETCOMPONENT_HPP_
#define PRESETCOMPONENT_HPP_

#include "Components/KeyboardPreset.hpp"

namespace is::components {

    class KeyboardPresetComponent;

    class PresetComponent: public is::ecs::Component {

    public:
        PresetComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            int number = 0
            );
        ~PresetComponent() = default;

        PresetComponent(const PresetComponent &) = delete;
        PresetComponent &operator=(const PresetComponent &) = delete;

        [[nodiscard]] KeyboardPresetComponent &getKeyboardPreset();

    private:
        KeyboardPresetComponent _keyboardPreset;

    public:
        int presetNumber;

    };

}

#endif /* !PRESETCOMPONENT_HPP_ */
