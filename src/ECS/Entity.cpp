/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entity
*/

#include "ECS/Entity.hpp"

using namespace is::ecs;

Entity::Entity(Layer entityLayer): layer(entityLayer), _active(false), _delete(false)
{
    static int id = 0;

    _id = id++;
}

void Entity::setDelete(bool set)
{
    _delete = set;
}

bool Entity::shouldBeDeleted() const
{
    return _delete;
}

bool Entity::isInit() const
{
    return _active;
}

void Entity::setInit(bool active)
{
    _active = active;
}

std::vector<std::shared_ptr<Component>> is::ecs::Entity::getComponents() const
{
    return (_components);
}
