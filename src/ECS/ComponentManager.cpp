/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComponentManager
*/

#include "ECS/ComponentManager.hpp"

is::ecs::ComponentManager::ComponentManager()
{

}

is::ecs::ComponentManager::~ComponentManager()
{
}

void is::ecs::ComponentManager::addComponent(std::weak_ptr<Component> component)
{
    auto spt = component.lock();

    _components[typeid(*spt).hash_code()].push_back(component);
}

std::vector<std::weak_ptr<is::ecs::Component>> &is::ecs::ComponentManager::getComponentsByType(size_t type)
{
    return (_components[type]);
}