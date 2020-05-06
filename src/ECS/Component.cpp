/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Component
*/

#include "ECS/Component.hpp"

is::ecs::Component::Component(Entity &e): _entity(e)
{}

is::ecs::Entity &is::ecs::Component::getEntity()
{
    return (_entity);
}
