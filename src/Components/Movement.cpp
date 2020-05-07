/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#include "Components/Movement.hpp"

using namespace is::components;

MovementComponent::MovementComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    TransformComponent &transform,
    bool clip
    ): Component(e), clipping(clip), _transform(transform)
{}

TransformComponent &MovementComponent::getTransform() const noexcept
{
    return (_transform);
}
