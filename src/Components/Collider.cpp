/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/Collider.hpp"

using namespace is::components;

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
    _transform(transform)
{}

const TransformComponent &ColliderComponent::getTransform() const noexcept
{
    return (_transform);
}
