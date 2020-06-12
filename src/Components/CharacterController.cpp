/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#include "Components/CharacterController.hpp"

using namespace is::components;
using namespace is::ecs;

CharacterControllerComponent::CharacterControllerComponent(
    std::shared_ptr<Entity> &e,
    TransformComponent &transform,
    MovementComponent &movementComponent,
    AudioComponent &footstep_1,
    AudioComponent &footstep_2,
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
    _footstep_1(footstep_1),
    _footstep_2(footstep_2),
    _character(character)
{
    static int id = 0;
    _id = id++;
}

void CharacterControllerComponent::deleteComponent()
{}

bool CharacterControllerComponent::operator==(const CharacterControllerComponent &character) const noexcept
{
    return (_id == character._id);
}

MovementComponent &CharacterControllerComponent::getMovementComponent() const noexcept
{
    return (_movementComponent);
}

TransformComponent &CharacterControllerComponent::getTransform() const noexcept
{
    return (_transform);
}

AudioComponent &CharacterControllerComponent::getAudioComponent() noexcept
{
    _fs_1 = !_fs_1;

    if (_fs_1)
        return _footstep_1;
    return _footstep_2;
}

CharacterComponent &CharacterControllerComponent::getCharacterComponent() const noexcept
{
    return (_character);
}

bool CharacterControllerComponent::shouldPlayFootstepSound(float secondsElapsed)
{
    _footstepElapsedTime += secondsElapsed;
    if (_footstepElapsedTime > 0.3) {
        _footstepElapsedTime -= 0.3;
        return true;
    }
    return false;
}
