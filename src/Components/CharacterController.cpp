/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#include "Components/CharacterController.hpp"

using namespace is::components;

ComponentCharacterController::ComponentCharacterController(
    std::shared_ptr<is::ecs::Entity> &e,
    TransformComponent &transform,
    MovementComponent &movementComponent,
    const std::string &wn,
    float ps,
    float playerJumpSpeed
    ):
    Component(e),
    rotateY(0),
    playerSpeed(ps),
    windowName(wn),
    jumpSpeed(playerJumpSpeed),
    _movementComponent(movementComponent),
    _transform(transform)
{
}

MovementComponent &ComponentCharacterController::getMovementComponent() const noexcept
{
    return (_movementComponent);
}

TransformComponent &ComponentCharacterController::getTransform() const noexcept
{
    return (_transform);
}
