/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomberman
*/

#include "Components/Bomberman.hpp"

using namespace is::components;
using namespace is::ecs;

BombermanComponent::BombermanComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    CharacterComponent &character
) : Component(e),
    bombNumber(1),
    bombRange(1),
    speedCount(0),
    speedMult(1),
    wallPass(false),
    instantBomb(0),
    dead(false),
    deathTimer(0.7f),
    _character(character)
{
}

void BombermanComponent::deleteComponent()
{
}

CharacterComponent &BombermanComponent::getCharacter() const noexcept
{
    return (_character);
}