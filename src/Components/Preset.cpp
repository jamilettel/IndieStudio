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
    Component(e), _keyboardPreset(e), presetNumber(number)
{}

KeyboardPresetComponent &PresetComponent::getKeyboardPreset()
{
    return _keyboardPreset;
}
