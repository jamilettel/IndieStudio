/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickPreset
*/

#include "Components/JoystickPreset.hpp"

using namespace is::components;
using namespace is::ecs;
using namespace is;

JoystickPresetComponent::JoystickPresetComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e)
{}

void JoystickPresetComponent::deleteComponent()
{}

// void JoystickPresetComponent::unbindButton(u32 button)
// {
//     for (auto it = _buttons.begin(); it != _buttons.end(); it++) {
//         if (it->second == button) {
//             _buttons.erase(it);
//             return;
//         }
//     }
// }

// bool JoystickPresetComponent::isButtonBound(u32 button) const
// {
//     for (auto &elem: _buttons) {
//         if (elem.second == button)
//             return true;
//     }
//     return false;
// }

bool JoystickPresetComponent::isBound(s32 binding) const
{
    for (auto &elem: _bindings) {
        if (elem.second == binding)
            return true;
    }
    return false;
}

// bool JoystickPresetComponent::isAxisBound(u32 axis) const
// {
//     for (auto &elem: _axes) {
//         if (elem.second == axis)
//             return true;
//     }
//     return false;
// }

// void JoystickPresetComponent::bindButton(u32 button, const PresetAction &action)
// {
//     _buttons[action] = button;
// }

void JoystickPresetComponent::bind(s32 binding, const PresetAction &action)
{
    _bindings[action] = binding;
}

// void JoystickPresetComponent::unbindAxis(u32 axis)
// {
//     for (auto it = _axes.begin(); it != _axes.end(); it++) {
//         if (it->second == axis)
//             _axes.erase(it);
//     }
// }

// void JoystickPresetComponent::bindAxis(u32 button, const PresetAction &action)
// {
//     _axes[action] = button;
// }

bool JoystickPresetComponent::changeBinding(s32 from, s32 to)
{
    auto it = std::find_if(
        _bindings.begin(), _bindings.end(),
        [&from] (const std::pair<PresetAction, s32> &pair) {
            if (pair.second == from)
                return true;
            return false;
        });

    if (it == _bindings.end())
        return false;
    it->second = to;
    return true;
}

// bool JoystickPresetComponent::changeButton(u32 from, u32 to)
// {
//     auto it = std::find_if(
//         _buttons.begin(), _buttons.end(),
//         [&from] (const std::pair<PresetAction, u32> &pair) {
//             if (pair.second == from)
//                 return true;
//             return false;
//         });

//     if (it == _buttons.end())
//         return false;
//     it->second = to;
//     return true;
// }

// bool JoystickPresetComponent::changeAxis(u32 from, u32 to)
// {
//     auto it = std::find_if(
//         _axes.begin(), _axes.end(),
//         [&from] (const std::pair<PresetAction, u32> &pair) {
//             if (pair.second == from)
//                 return true;
//             return false;
//         });

//     if (it == _axes.end())
//         return false;
//     it->second = to;
//     return true;
// }

// const std::map<PresetAction, u32> &JoystickPresetComponent::getButtonBindings() const
// {
//     return _buttons;
// }

// const std::map<PresetAction, u32> &JoystickPresetComponent::getAxisBindings() const
// {
//     return _axes;
// }

const std::map<PresetAction, s32> &JoystickPresetComponent::getBindings() const
{
    // std::map<PresetAction, u32> bindings;

    // bindings.insert(_buttons.begin(), _buttons.end());
    // bindings.insert(_axes.begin(), _axes.end());

    return _bindings;
}


void JoystickPresetComponent::createBasicPreset(JoystickPresetComponent &preset)
{
    preset.bind(1, PresetAction("MoveVerticalAxis", 1, "Move forward", true));
    preset.bind(1, PresetAction("MoveVerticalAxis", -1, "Move backward", false));
    preset.bind(0, PresetAction("MoveHorizontalAxis", -1, "Move right", false));
    preset.bind(0, PresetAction("MoveHorizontalAxis", 1, "Move left", true));
    preset.bind(-3, PresetAction("DropBomb", 1, "Drop bomb", false));
    preset.bind(-1, PresetAction("Jump", 1, "Jump", false));
}
