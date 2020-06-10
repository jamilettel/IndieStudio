/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickPreset
*/

#include "Components/JoystickPreset.hpp"

using namespace is::components;
using namespace is::ecs;

JoystickPresetComponent::JoystickPresetComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e)
{
}

void JoystickPresetComponent::deleteComponent()
{
}

bool JoystickPresetComponent::isBound(irr::s32 binding) const
{
    for (auto &elem: _bindings) {
        if (elem.second == binding)
            return true;
    }
    return false;
}

void JoystickPresetComponent::bind(irr::s32 binding, const PresetAction &action)
{
    _bindings[action] = binding;
}

bool JoystickPresetComponent::changeBinding(irr::s32 from, irr::s32 to)
{
    auto it = std::find_if(
        _bindings.begin(), _bindings.end(),
        [&from] (const std::pair<PresetAction, irr::s32> &pair) {
            return pair.second == from;
        });

    if (it == _bindings.end())
        return false;
    it->second = to;
    return true;
}

const std::map<is::PresetAction, irr::s32> &JoystickPresetComponent::getBindings() const
{
    return _bindings;
}

void JoystickPresetComponent::bindAxis(irr::s32 binding, const PresetAction &action)
{
    auto other = std::find_if(
        _bindings.begin(), _bindings.end(),
        [&action] (const std::pair<PresetAction, irr::s32> &pair)-> bool {
            return action.action == pair.first.action && action.max != pair.first.max;
        });

    bind(binding, action);
    if (other != _bindings.end()) {
        bind(binding, other->first);
    }
}

void JoystickPresetComponent::createBasicPreset(JoystickPresetComponent &preset)
{
    preset.bind(1, PresetAction("MoveVerticalAxis", 1, "Move forward", true));
    preset.bind(1, PresetAction("MoveVerticalAxis", -1, "Move backward", false));
    preset.bind(0, PresetAction("MoveHorizontalAxis", -1, "Move right", false));
    preset.bind(0, PresetAction("MoveHorizontalAxis", 1, "Move left", true));
    preset.bind(-3, PresetAction("DropBomb", 1, "Drop bomb", false));
    preset.bind(-8, PresetAction("Pause", 1, "Pause menu", false));
}
