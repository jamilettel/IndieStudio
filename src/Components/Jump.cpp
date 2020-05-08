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
    _jump = jump;
}

bool JumpComponent::isJump() const noexcept
{
    return (_jump);
}

MovementComponent &JumpComponent::getMovement() const noexcept
{
    return (_movement);
}