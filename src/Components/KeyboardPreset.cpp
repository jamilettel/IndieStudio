/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardPreset
*/

#include "Components/KeyboardPreset.hpp"

using namespace is::components;
using namespace is::ecs;

KeyboardPresetComponent::KeyboardPresetComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e)
{}

void KeyboardPresetComponent::deleteComponent()
{}

bool KeyboardPresetComponent::isBound(irr::EKEY_CODE key) const
{
    for (auto &elem: _bindings)
        if (elem.second == key)
            return true;
    return false;
}

void KeyboardPresetComponent::bind(irr::EKEY_CODE key, const PresetAction &action)
{
    _bindings[action] = key;
}

bool KeyboardPresetComponent::changeKey(irr::EKEY_CODE from, irr::EKEY_CODE to)
{
    if (isBound(to))
        return false;
    auto it = std::find_if(
        _bindings.begin(), _bindings.end(),
        [from] (const std::pair<PresetAction, irr::EKEY_CODE> &pair) {
            return pair.second == from;
        });
    if (it == _bindings.end())
        return false;
    it->second = to;
    return true;
}

const std::map<is::PresetAction, irr::EKEY_CODE> &KeyboardPresetComponent::getBindings() const
{
    return _bindings;
}

void KeyboardPresetComponent::createBasicPreset(KeyboardPresetComponent &preset)
{
    preset.bind(irr::KEY_KEY_W, PresetAction("MoveVerticalAxis", 1, "Move forward"));
    preset.bind(irr::KEY_KEY_S, PresetAction("MoveVerticalAxis", -1, "Move backward"));
    preset.bind(irr::KEY_KEY_D, PresetAction("MoveHorizontalAxis", -1, "Move right"));
    preset.bind(irr::KEY_KEY_A, PresetAction("MoveHorizontalAxis", 1, "Move left"));
    preset.bind(irr::KEY_KEY_E, PresetAction("DropBomb", 1, "Drop bomb"));
    preset.bind(irr::KEY_SPACE, PresetAction("Jump", 1, "Jump"));
}
