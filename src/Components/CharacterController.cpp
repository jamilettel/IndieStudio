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
    ComponentAudio &audio,
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
    _transform(transform),
    _audioComponent(audio)
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

ComponentAudio &ComponentCharacterController::getAudioComponent() const noexcept
{
    return (_audioComponent);
}
