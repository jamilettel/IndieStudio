/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** InputManager
*/

#include "Components/InputManager.hpp"
#include <algorithm>

using namespace is::components;

InputManagerComponent::InputManagerComponent(
    std::shared_ptr<is::ecs::Entity> &e
    ):
    is::ecs::Component(e)
{}

void InputManagerComponent::deleteComponent()
{}

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
