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
    ColliderComponent &collider,
    bool clip
    ): Component(e), clipping(clip), _transform(transform), _collider(collider)
{}

void MovementComponent::deleteComponent()
{
    
}

TransformComponent &MovementComponent::getTransform() const noexcept
{
    return (_transform);
}

ColliderComponent &MovementComponent::getCollider() const noexcept
{
    return (_collider);
}

bool MovementComponent::isOnTheGround() const noexcept
{
    return (_isOnTheGround);
}

void MovementComponent::setOnTheGround(bool isOnTheGround) noexcept
{
    _isOnTheGround = isOnTheGround;
}