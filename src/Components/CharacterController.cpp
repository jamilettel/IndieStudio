/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#include "Components/CharacterController.hpp"

#include <utility>

using namespace is::components;

CharacterControllerComponent::CharacterControllerComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    TransformComponent &transform,
    MovementComponent &movementComponent,
    AudioComponent &audio,
    CharacterComponent &character,
    std::string wn,
    float ps
    ):
    Component(e),
    rotateY(0),
    playerSpeed(ps),
    windowName(std::move(wn)),
    _movementComponent(movementComponent),
    _transform(transform),
    _audioComponent(audio),
    _character(character)
{
}

void CharacterControllerComponent::deleteComponent()
{
    
}

MovementComponent &CharacterControllerComponent::getMovementComponent() const noexcept
{
    return (_movementComponent);
}

TransformComponent &CharacterControllerComponent::getTransform() const noexcept
{
    return (_transform);
}

AudioComponent &CharacterControllerComponent::getAudioComponent() const noexcept
{
    return (_audioComponent);
}

CharacterComponent &CharacterControllerComponent::getCharacterComponent() const noexcept
{
    return (_character);
}