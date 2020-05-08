/*
** EPITECH PROJECT, 2020
** Systems/TextSystem.cpp
** File description:
** 
*/

#include "Systems/Text.hpp"
#include "Components/Text.hpp"

#include <algorithm>
#include <iostream>

using namespace is::systems;
using namespace is::components;

void TextSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(TextComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<TextComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("TextSystem", "Could not getTextComponent pointer");
        
        std::shared_ptr<WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("TextComponent", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("TextComponent", "Could not found window");

        ptr->init(ptr_window);
    }
}

void TextSystem::start()
{
}

void TextSystem::update()
{
}

void TextSystem::stop()
{
}

void TextSystem::onTearDown()
{
}

