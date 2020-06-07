/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#include "Systems/JoystickCursor.hpp"
#include "Components/JoystickCursor.hpp"
#include "Components/Button.hpp"

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
    _time = std::static_pointer_cast<TimeComponent>(timeList[0]);
}

void JoystickCursorSystem::start()
{}

void JoystickCursorSystem::update()
{
    const auto &joystickCursors = _componentManager->getComponentsByType(typeid(JoystickCursorComponent).hash_code());
    const auto &buttons = _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code());

    for (const auto &cursor: joystickCursors) {
        const auto &ptr = static_cast<JoystickCursorComponent *>(cursor.get());
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

        bool click = ptr->getJoystickInput().getInputManager().getInput("Click") == 1;
        if (!click && ptr->clicked) {
            for (const auto &button: buttons) {
                const auto &buttonPtr = static_cast<ButtonComponent*>(button.get());

                if (buttonPtr->contains(ptr->getCursor().getPosition())) {
                    buttonPtr->callCallback(ptr->getJoystickId());
                }
            }
        }
        ptr->clicked = click;
    }
}

void JoystickCursorSystem::stop()
{
}

void JoystickCursorSystem::onTearDown()
{
}
