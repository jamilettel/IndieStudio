/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Preset
*/

#ifndef PRESETCOMPONENT_HPP_
#define PRESETCOMPONENT_HPP_

#include "Components/KeyboardPreset.hpp"
#include "Components/JoystickPreset.hpp"

namespace is::components {

    class KeyboardPresetComponent;

    class PresetComponent : public is::ecs::Component {

    public:
        PresetComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            int number = 0
            );
        ~PresetComponent() = default;

        PresetComponent(const PresetComponent &) = delete;
        PresetComponent &operator=(const PresetComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] KeyboardPresetComponent &getKeyboardPreset();
        [[nodiscard]] JoystickPresetComponent &getJoystickPreset();

    private:
        KeyboardPresetComponent _keyboardPreset;
        JoystickPresetComponent _joystickPreset;

    public:
        int presetNumber;

    };

}

#endif /* !PRESETCOMPONENT_HPP_ */
