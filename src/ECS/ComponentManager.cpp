/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComponentManager
*/

#include "ECS/ComponentManager.hpp"

void is::ecs::ComponentManager::addComponent(std::shared_ptr<Component> component)
{
    auto& r = *component.get();

    _components[typeid(r).hash_code()].push_back(component);
}

std::vector<std::shared_ptr<is::ecs::Component>> &is::ecs::ComponentManager::getComponentsByType(size_t type)
{
    return (_components[type]);
}
