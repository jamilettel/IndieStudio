/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Preset
*/

#include "Components/Preset.hpp"

using namespace is::ecs;
using namespace is::components;

PresetComponent::PresetComponent(
    std::shared_ptr<Entity> &e,
    int number
    ) : Component(e), _keyboardPreset(e), _joystickPreset(e), presetNumber(number), _toChange(), _toChangeUI(), _onSelect(false), _callerID(-1)
{
}

void PresetComponent::deleteComponent()
{
}

KeyboardPresetComponent &PresetComponent::getKeyboardPreset()
{
    return _keyboardPreset;
}

JoystickPresetComponent &PresetComponent::getJoystickPreset()
{
    return _joystickPreset;
}

std::string PresetComponent::getEquivalentKey(irr::EKEY_CODE key)
{
    for (int i = 0; PresetComponent::EquivalentKeys[i]._key != irr::EKEY_CODE::KEY_KEY_CODES_COUNT; i++) {
        if (PresetComponent::EquivalentKeys[i]._key == key)
            return PresetComponent::EquivalentKeys[i]._name;
    }
    return "Unknown";
}

std::string PresetComponent::getEquivalentButton(int button)
{
    for (int i = 0; PresetComponent::EquivalentButtons[i]._button != -9999; i++) {
        if (PresetComponent::EquivalentButtons[i]._button == button)
            return PresetComponent::EquivalentButtons[i]._filename;
    }
    return "Unknown";
}