/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickInput
*/

#include "Systems/JoystickInput.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void JoystickInputSystem::awake()
{
}

void JoystickInputSystem::start()
{
    auto windows = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());

    if (windows.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Window component required for Keyboard Input System");
    const auto &window = static_cast<WindowComponent*>(windows[0].get());
    _joysticks.emplace(window->joysticks);
    _eventManager.emplace(window->eventManager);
}

void JoystickInputSystem::stop()
{}

void JoystickInputSystem::onTearDown()
{}

void JoystickInputSystem::update()
{
    const auto &joystickComponents = _componentManager->getComponentsByType(typeid(JoystickInputComponent).hash_code());

    for (const auto &component: joystickComponents) {
        const auto &joystick = *static_cast<JoystickInputComponent *>(component.get());
        const auto &buttonBindings = joystick.getButtonBindings();
        const auto &axisBindings = joystick.getAxisBindings();
        size_t pos = 0;

        for (; pos < _joysticks->get().size(); pos++)
            if (_joysticks->get()[pos].Joystick == joystick.getJoystickId())
                break;

        joystick.getInputManager().resetValues();

        for (const auto &pair: buttonBindings) {
            if (_eventManager->get().isJoystickButtonPressed(joystick.getJoystickId(), pair.first))
                joystick.getInputManager().addValue(pair.second.first, pair.second.second);
        }
        for (const auto &pair: axisBindings) {
            irr::s16 axis = _eventManager->get().getAxisValue(joystick.getJoystickId(), pair.first);
            float value = static_cast<float>(axis) / JOYSTICK_MAX_AXIS_VALUE;

            if ((value >= 0 && value <= joystick.axisDeadzoneMin) ||
                (value < 0 && value >= -joystick.axisDeadzoneMin))
                value = 0;
            else if (value > 0 && value >= joystick.axisDeadzoneMax)
                value = 1;
            else if (value < 0 && -value >= joystick.axisDeadzoneMax)
                value = -1;
            if (value < 0)
                value = -value * pair.second.second[1];
            else if (value > 0)
                value = value * pair.second.second[0];

            joystick.getInputManager().addValue(pair.second.first, value);
        }
    }
}
