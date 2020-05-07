/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Gravity
*/

#include "Components/Gravity.hpp"

using namespace is::components;

GravityComponent::GravityComponent(std::shared_ptr<is::ecs::Entity> &e, MovementComponent &movement) : Component(e), _movement(movement)
{
}

void GravityComponent::deleteComponent()
{
    
}

void GravityComponent::setActive(bool active)
{
    _active = active;
}

bool GravityComponent::isActive() const noexcept
{
    return (_active);
}

MovementComponent &GravityComponent::getMovement() const noexcept
{
    return (_movement);
}