/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickInput
*/

#include "Components/JoystickInput.hpp"

using namespace is::components;
using namespace is::ecs;

JoystickInputComponent::JoystickInputComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    InputManagerComponent &inputManager
    ):
    Component(e),
    _inputManager(inputManager)
{}

void JoystickInputComponent::deleteComponent()
{}

bool JoystickInputComponent::isButtonBound(u32 key) const
{
    return _buttons.count(key) == 1;
}

bool JoystickInputComponent::isAxisBound(u32 axis) const
{
    return _axes.count(axis) == 1;
}

void JoystickInputComponent::bindButton(u32 button, const std::string &action, float target)
{
    _buttons[button].first = action;
    _buttons[button].second = target;
}

void JoystickInputComponent::bindAxis(u32 axis, const std::string &action, float min, float max)
{
    _axes[axis].first = action;
    _axes[axis].second[0] = min;
    _axes[axis].second[1] = max;
}

void JoystickInputComponent::unbindButton(u32 axis)
{
    auto it = _buttons.find(axis);

    if (it != _buttons.end())
        _buttons.erase(it);
}

void JoystickInputComponent::unbindAxis(u32 axis)
{
    auto it = _axes.find(axis);

    if (it != _axes.end())
        _axes.erase(it);
}

bool JoystickInputComponent::changeButton(u32 from, u32 to)
{
    auto it = _buttons.find(from);

    if (it == _buttons.end() || !isButtonBound(to))
        return false;
    _buttons[to] = it->second;
    _buttons.erase(it);
    return true;
}

bool JoystickInputComponent::changeAxis(u32 from, u32 to)
{
    auto it = _axes.find(from);

    if (it == _axes.end() || !isButtonBound(to))
        return false;
    _axes[to].first = it->second.first;
    _axes[to].second[0] = it->second.second[0];
    _axes[to].second[1] = it->second.second[1];
    _axes.erase(it);
    return true;
}

bool JoystickInputComponent::changeButtonTarget(u32 button, float target)
{
    auto it = _buttons.find(button);

    if (it == _buttons.end())
        return false;
    it->second.second = target;
    return true;
}

bool JoystickInputComponent::changeAxisTarget(u32 axis, float min, float max)
{
    auto it = _axes.find(axis);

    if (it == _axes.end())
        return false;
    it->second.second[0] = min;
    it->second.second[1] = max;
    return true;
}

std::map<u32, std::pair<std::string, float>> &JoystickInputComponent::getButtonBindings()
{
    return _buttons;
}

std::map<u32, std::pair<std::string, float[2]>> &JoystickInputComponent::getAxisBindings()
{
    return _axes;
}

InputManagerComponent &JoystickInputComponent::getInputManager() const
{
    return _inputManager;
}

void JoystickInputComponent::assignJoystick(int id)
{
    _joystickId = id;
}

int JoystickInputComponent::getJoystickId() const
{
    return _joystickId;
}
