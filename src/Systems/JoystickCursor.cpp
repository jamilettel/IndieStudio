/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#include "Systems/JoystickCursor.hpp"
#include "Components/JoystickCursor.hpp"

using namespace is::ecs;
using namespace is::systems;
using namespace is::components;

void JoystickCursorSystem::awake()
{}

void JoystickCursorSystem::start()
{}

void JoystickCursorSystem::update()
{
    auto joystickCursors = _componentManager->getComponentsByType(typeid(JoystickCursorComponent).hash_code());

    for (auto cursor: joystickCursors) {
        auto ptr = static_cast<JoystickCursorComponent *>(cursor.get());
        float horizontal = ptr->getJoystickInput().getInputManager().getInput("Horizontal") * 20.0;
        float vertical = ptr->getJoystickInput().getInputManager().getInput("Vertical") * 20.0;
        auto pos = ptr->getCursor().getPosition();
        ptr->getCursor().setPosition(pos.X + horizontal, pos.Y + vertical);
    }
}

void JoystickCursorSystem::stop()
{}

void JoystickCursorSystem::onTearDown()
{}
