/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Component
*/

#include "ECS/Component.hpp"

is::ecs::Component::Component(std::shared_ptr<Entity> &e): _entity(e)
{}

std::shared_ptr<is::ecs::Entity> is::ecs::Component::getEntity() const noexcept
{
    return (_entity);
}
