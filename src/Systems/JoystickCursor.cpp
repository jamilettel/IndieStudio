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
{
    auto &windows = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());

    if (!windows.size())
        throw is::exceptions::Exception("JoystickCursorSystem", "Could not find Window Component");
    auto ptr = static_cast<WindowComponent *>(windows[0].get());

    _windowSize.X = ptr->_width;
    _windowSize.Y = ptr->_height;

    auto &timeList = _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());
    if (timeList.size() == 0)
        throw is::exceptions::Exception("JoystickCursorSystem", "Could not find Time Component");
    _time = std::dynamic_pointer_cast<TimeComponent>(timeList[0]);
}

void JoystickCursorSystem::start()
{}

void JoystickCursorSystem::update()
{
    auto joystickCursors = _componentManager->getComponentsByType(typeid(JoystickCursorComponent).hash_code());

    for (auto cursor: joystickCursors) {
        auto ptr = static_cast<JoystickCursorComponent *>(cursor.get());
        float horizontal = ptr->getJoystickInput().getInputManager().getInput("Horizontal") * _time->getCurrentIntervalMilliseconds();
        float vertical = ptr->getJoystickInput().getInputManager().getInput("Vertical") * _time->getCurrentIntervalMilliseconds();
        auto pos = ptr->getCursor().getPosition();
        pos.X += horizontal;
        if (pos.X > _windowSize.X)
            pos.X = _windowSize.X;
        else if (pos.X < 0)
            pos.X = 0;
        pos.Y += vertical;
        if (pos.Y > _windowSize.Y)
            pos.Y = _windowSize.Y;
        else if (pos.Y < 0)
            pos.Y = 0;
        ptr->getCursor().setPosition(pos.X, pos.Y);
    }
}

void JoystickCursorSystem::stop()
{}

void JoystickCursorSystem::onTearDown()
{}
