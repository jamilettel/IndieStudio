/*
** EPITECH PROJECT, 2020
** Systems/SliderSystem.cpp
** File description:
** 
*/

#include "Systems/Slider.hpp"
#include "Components/Slider.hpp"
#include <algorithm>
#include <iostream>
using namespace is::systems;
using namespace is::components;

void SliderSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(SliderComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<SliderComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("SliderSystem", "Could not getSliderComponent pointer");
        
        std::shared_ptr<WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("SliderComponent", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("SliderComponent", "Could not found window");

        ptr->init(ptr_window);
    }
}

void SliderSystem::start()
{
}

void SliderSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(SliderComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<SliderComponent>(elem);
        if (ptr->isPressed()) {
            std::shared_ptr<WindowComponent> ptr_window;
            bool windowFound = false;
            for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
                ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
                if (!ptr_window)
                    throw new is::exceptions::Exception("SliderComponent", "Could not get WindowComponent pointer");
                if (ptr_window->windowName == ptr->windowName) {
                    windowFound = true;
                    break;
                }
            }
            if (!windowFound)
            throw new is::exceptions::Exception("SliderSystem", "Could not found window");
            ptr->setPosition(ptr_window->eventManager.getMousePosition().first);
        }
    }
}

void SliderSystem::stop()
{
}

void SliderSystem::onTearDown()
{
}

