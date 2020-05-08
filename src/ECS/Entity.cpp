/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entity
*/

#include "ECS/Entity.hpp"

is::ecs::Entity::Entity(Layer entityLayer): layer(entityLayer), _active(true), _delete(false)
{
    static int id = 0;

    _id = id++;
}

void is::ecs::Entity::setDelete(bool set)
{
    _delete = set;
}

bool is::ecs::Entity::shouldBeDeleted() const
{
    return _delete;
}

bool is::ecs::Entity::isActive() const
{
    return _active;
}

void is::ecs::Entity::setActive(bool active)
{
    _active = active;
}

std::vector<std::shared_ptr<is::ecs::Component>> is::ecs::Entity::getComponents() const
{
    return (_components);
}
