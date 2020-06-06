/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetAction
*/

#include "PresetAction.hpp"

using namespace is;

PresetAction::PresetAction(
    std::string actionString,
    float target,
    std::string desc,
    bool maximum
    ):
    action(std::move(actionString)),
    value(target),
    description(std::move(desc)),
    max(maximum)
{}

bool PresetAction::operator<(const PresetAction &rhs) const
{
    if (action != rhs.action)
        return action < rhs.action;
    return value < rhs.value;
}

bool PresetAction::operator>(const PresetAction &rhs) const
{
    if (action != rhs.action)
        return action > rhs.action;
    return value > rhs.value;
}

bool PresetAction::operator==(const PresetAction &rhs) const
{
    return action == rhs.action && value == rhs.value && description == rhs.description;
}
