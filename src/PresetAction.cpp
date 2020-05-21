/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetAction
*/

#include "PresetAction.hpp"

using namespace is;

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
