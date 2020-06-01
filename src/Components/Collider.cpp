/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/Collider.hpp"

using namespace is::components;
using namespace is::ecs;

ColliderComponent::ColliderComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    TransformComponent &transform,
    const irr::core::vector3df &colliderSize,
    const irr::core::vector3df &colliderOffset,
    bool check
    ):
    Component(e),
    offset(colliderOffset),
    size(colliderSize),
    activeCheck(check),
    distance(0),
    _transform(transform)
{}

void ColliderComponent::deleteComponent()
{}

const TransformComponent &ColliderComponent::getTransform() const noexcept
{
    return (_transform);
}

void ColliderComponent::addCollisionWithLayer(is::ecs::Entity::Layer layer)
{
    _layers.emplace_back(layer);
}

void ColliderComponent::removeCollisionWithLayer(is::ecs::Entity::Layer layer)
{
    _layers.erase(std::remove(_layers.begin(), _layers.end(), layer), _layers.end());
}

bool ColliderComponent::collidesWith(is::ecs::Entity::Layer layer)
{
    return (std::find(_layers.begin(), _layers.end(), layer) != _layers.end());
}
