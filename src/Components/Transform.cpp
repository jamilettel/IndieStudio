/*
** EPITECH PROJECT, 2020
** Indie stdui
** File description:
** TransformSystem
*/

#include "Components/Transform.hpp"

using namespace is::components;

TransformComponent::TransformComponent(std::shared_ptr<is::ecs::Entity> &e,
irr::core::vector3df pos, irr::core::vector3df rot, irr::core::vector3df scl):
    position(pos),
    rotation(rot),
    scale(scl),
    Component(e)
{}

void TransformComponent::move(const irr::core::vector3df &vector)
{
    this->position += vector;
}

void TransformComponent::rotate(const irr::core::vector3df &vector)
{
    this->rotation += vector;
}

void TransformComponent::scaleObject(const irr::core::vector3df &vector)
{
    this->scale *= vector;
}
