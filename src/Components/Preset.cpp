/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Preset
*/

#include "Components/Preset.hpp"

using namespace is::components;

PresetComponent::PresetComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    int number
    ):
    Component(e), _keyboardPreset(e), _joystickPreset(e), presetNumber(number)
{}

void PresetComponent::deleteComponent()
{}

KeyboardPresetComponent &PresetComponent::getKeyboardPreset()
{
    return _keyboardPreset;
}

JoystickPresetComponent &PresetComponent::getJoystickPreset()
{
    return _joystickPreset;
}
