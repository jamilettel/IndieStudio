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
    for (const auto &elem : _componentManager->getComponentsByType(typeid(SliderComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<SliderComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("SliderSystem", "Could not getSliderComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [&ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("SliderComponent", "Could not find window");

        _window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->init(_window);
    }
}

void SliderSystem::start()
{
}

void SliderSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(SliderComponent).hash_code())) {
        const auto &ptr = static_cast<SliderComponent*>(elem.get());
        if (ptr->isPressed()) {
            ptr->setPosition(_window->eventManager.getMousePosition().first);
        }
    }
}

void SliderSystem::stop()
{
}

void SliderSystem::onTearDown()
{
}

