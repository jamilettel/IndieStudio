/*
** EPITECH PROJECT, 2020
** Indie stdui
** File description:
** TransformSystem
*/

#include "Components/Transform.hpp"

using namespace is::ecs;
using namespace is::components;

TransformComponent::TransformComponent(std::shared_ptr<Entity> &e,
                                       const irr::core::vector3df& pos,
                                       const irr::core::vector3df& rot,
                                       const irr::core::vector3df& scl):
Component(e),
position(pos),
rotation(rot),
scale(scl)
{
}

void TransformComponent::deleteComponent()
{
    
}

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
