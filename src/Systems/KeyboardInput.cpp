/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardInput
*/

#include "Systems/KeyboardInput.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void KeyboardInputSystem::awake()
{}

void KeyboardInputSystem::start()
{
    const auto &window = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());

    if (window.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Window component required for Keyboard Input System");
    _window = std::static_pointer_cast<WindowComponent>(window[0]);
}

void KeyboardInputSystem::stop()
{}

void KeyboardInputSystem::onTearDown()
{}

void KeyboardInputSystem::update()
{
    const auto &keyboardComponents = _componentManager->getComponentsByType(typeid(KeyboardInputComponent).hash_code());

    for (const auto &component: keyboardComponents) {
        const auto &keyboard = *static_cast<KeyboardInputComponent *>(component.get());
        auto &bindings = keyboard.getBindings();
        auto &manager = keyboard.getInputManager();

        manager.resetValues();

        for (const auto &pair: bindings) {
            if (_window->eventManager.IsKeyDown(pair.first))
                manager.addValue(pair.second.first, pair.second.second);
        }
    }
}
