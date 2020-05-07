/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/Collider.hpp"

using namespace is::components;

ColliderComponent::ColliderComponent(std::shared_ptr<is::ecs::Entity> &e,
                                     bool check,
                                     TransformComponent &transform):
Component(e),
activeCheck(check),
_transform(transform)
{}

const TransformComponent &ColliderComponent::getTransform() const noexcept
{
    return (_transform);
}
