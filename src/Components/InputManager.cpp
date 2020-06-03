/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** InputManager
*/

#include "Components/InputManager.hpp"

using namespace is::components;
using namespace is::ecs;

InputManagerComponent::InputManagerComponent(
    std::shared_ptr<Entity> &e
    ):
    is::ecs::Component(e)
{
}

void InputManagerComponent::deleteComponent()
{
}

void InputManagerComponent::resetValues()
{
    std::for_each(
        _actions.begin(), _actions.end(),
        [] (std::pair<const std::string, float> &pair) {
            pair.second = 0;
        });
}

void InputManagerComponent::addValue(const std::string &action, float value)
{
    _actions[action] += value;
}

void InputManagerComponent::setValue(const std::string &action, float value)
{
    _actions[action] = value;
}

float InputManagerComponent::getInput(const std::string &action) const
{
    return (_actions.at(action));
}

void InputManagerComponent::resetValue(const std::string &action)
{
    if (_actions.find(action) == _actions.end())
        return;
    _actions[action] = 0;
}

bool InputManagerComponent::isActionSet(const std::string &action)
{
    return !(_actions.find(action) == _actions.end());
}
