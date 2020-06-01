/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#include "ECS/EntityManager.hpp"

using namespace is::ecs;

void EntityManager::addEntity(std::shared_ptr<Entity> &entity)
{
    _entities.push_back(entity);
}

void EntityManager::deleteEntities(std::shared_ptr<ComponentManager> &cm)
{
    auto i = std::begin(_entities);

    while (i != std::end(_entities)) {
        if (i->get()->shouldBeDeleted()) {
            for (auto &elem : i->get()->getComponents()) {
                cm->removeComponent(elem);
            }
            i = _entities.erase(i);
        }
        else
            i++;
    }
}

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities() const
{
    return (_entities);
}

bool EntityManager::operator()(std::shared_ptr<Entity> &ent)
{
    for (const auto& tmpEnt : _entities) {
        if (tmpEnt == ent)
            return (true);
    }
    return (false);
}
