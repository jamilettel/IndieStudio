/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entity
*/

#include "ECS/Entity.hpp"

is::ecs::Entity::Entity(): _actif(true), _delete(false)
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
    return (_delete);
}
