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

void is::ecs::ComponentManager::removeComponent(std::shared_ptr<Component> &component)
{
    component->deleteComponent();
    for (auto &elem : _components)
    {
        auto i = std::begin(elem.second);

        while (i != std::end(elem.second)) {
            if (*i == component)
                i = elem.second.erase(i);
            else
                i++;
        }
    }
    
}

std::vector<std::shared_ptr<is::ecs::Component>> &is::ecs::ComponentManager::getComponentsByType(size_t type)
{
    return (_components[type]);
}
