/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#include "ECS/EntityManager.hpp"

void is::ecs::EntityManager::addEntity(std::shared_ptr<Entity> &entity)
{
    _entities.push_back(entity);
}

void is::ecs::EntityManager::deleteEntities(std::shared_ptr<is::ecs::ComponentManager> &cm)
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

std::vector<std::shared_ptr<is::ecs::Entity>> is::ecs::EntityManager::getEntities() const
{
    return (_entities);
}

bool is::ecs::EntityManager::operator()(std::shared_ptr<is::ecs::Entity> &ent)
{
    for (auto tmpEnt : _entities) {
        if (tmpEnt == ent)
            return (false);
    }
    return (true);
}