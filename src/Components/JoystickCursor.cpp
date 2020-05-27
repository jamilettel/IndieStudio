/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#include "Components/JoystickCursor.hpp"
#include "ECS/Entity.hpp"

using namespace is::ecs;
using namespace is::components;

JoystickCursorComponent::JoystickCursorComponent(
    std::shared_ptr<is::ecs::Entity> &e,
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
