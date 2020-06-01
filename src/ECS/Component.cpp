/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Component
*/

#include "ECS/Component.hpp"

using namespace is::ecs;

Component::Component(std::shared_ptr<Entity> &e): _entity(e)
{
}

std::shared_ptr<Entity> Component::getEntity() const noexcept
{
    return (_entity);
}
