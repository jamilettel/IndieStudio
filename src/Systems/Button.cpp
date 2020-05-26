/*
** EPITECH PROJECT, 2020
** Systems/ButtonSystem.cpp
** File description:
** 
*/

#include "Systems/Button.hpp"
#include "Components/Button.hpp"

#include <algorithm>
#include <iostream>
using namespace is::systems;
using namespace is::components;

void ButtonSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<ButtonComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ButtonSystem", "Could not getButtonComponent pointer");

        std::shared_ptr<WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("ButtonComponent", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("ButtonComponent", "Could not find window");

        ptr->init(ptr_window);
        ptr_window->eventManager.addButton(ptr);
    }
}

void ButtonSystem::start()
{
}

void ButtonSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ButtonComponent>(elem);
        if (ptr->isClicked()) {
            ptr->callCallback();
            ptr->setClicked(false);
        }
    }
}

void ButtonSystem::stop()
{
}

void ButtonSystem::onTearDown()
{
    for (auto &elem: _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
        ptr->eventManager.removeAllButtons();
    }
}
