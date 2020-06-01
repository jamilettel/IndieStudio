/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComponentManager
*/

#include "ECS/ComponentManager.hpp"

using namespace is::ecs;

void ComponentManager::addComponent(const std::shared_ptr<Component>& component)
{
    auto& r = *component;

    _components[typeid(r).hash_code()].push_back(component);
}

void ComponentManager::removeComponent(std::shared_ptr<Component> &component)
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

std::vector<std::shared_ptr<Component>> &ComponentManager::getComponentsByType(size_t type)
{
    return _components[type];
}

const std::vector<std::shared_ptr<Component>> &ComponentManager::getComponentsByType(size_t type) const
{
    return _components.at(type);
}
