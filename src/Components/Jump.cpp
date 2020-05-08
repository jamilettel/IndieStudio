/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Jump
*/

#include "Components/Jump.hpp"

using namespace is::components;

JumpComponent::JumpComponent(std::shared_ptr<is::ecs::Entity> &e, MovementComponent &movement) : Component(e), _movement(movement)
{
}

void JumpComponent::deleteComponent()
{
}

void JumpComponent::setJump(bool jump)
{
    _isJumping = jump;
}

bool JumpComponent::isJumping() const noexcept
{
    return (_isJumping);
}

MovementComponent &JumpComponent::getMovement() const noexcept
{
    return (_movement);
}