/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#include "Components/JoystickCursor.hpp"

using namespace is::components;
using namespace is::ecs;

JoystickCursorComponent::JoystickCursorComponent(
    std::shared_ptr<Entity> &e,
    CursorComponent &cursor,
    JoystickInputComponent &joystickInput
    ):
    Component(e),
    _joystickInput(joystickInput),
    _cursor(cursor)
{}

void JoystickCursorComponent::deleteComponent()
{}

int JoystickCursorComponent::getJoystickId() const
{
    return _joystickInput.getJoystickId();
}

JoystickInputComponent &JoystickCursorComponent::getJoystickInput() const
{
    return _joystickInput;
}

WindowComponent &JoystickCursorComponent::getWindow() const
{
    return _cursor.getWindow();
}

CursorComponent &JoystickCursorComponent::getCursor() const
{
    return _cursor;
}
