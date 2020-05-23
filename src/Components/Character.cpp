/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#include "Components/Character.hpp"

using namespace is::components;
using namespace is::ecs;

CharacterComponent::CharacterComponent(std::shared_ptr<is::ecs::Entity> &e) : Component(e)
{
}

CharacterComponent::~CharacterComponent()
{
}

void CharacterComponent::setTimePlaying(size_t time) noexcept
{
    _timePlaying = time;
}

void CharacterComponent::setNbBombPosed(size_t nbBombPosed) noexcept
{
    _nbBombPosed = nbBombPosed;
}

void CharacterComponent::setNbBonusCollected(size_t nbBonusCollected) noexcept
{
    _nbBonusCollected = nbBonusCollected;
}

void CharacterComponent::setNbCharactersKilled(size_t nbCharactersKilled) noexcept
{
    _nbCharactersKilled = nbCharactersKilled;
}

int CharacterComponent::getTimePlaying() const noexcept
{
    return (_timePlaying);
}

int CharacterComponent::getNbBombPosed() const noexcept
{
    return (_nbBombPosed);
}

int CharacterComponent::getNbBonueCollected() const noexcept
{
    return (_nbBonusCollected);
}

int CharacterComponent::getNbCharactersKilled() const noexcept
{
    return (_nbCharactersKilled);
}

void CharacterComponent::deleteComponent()
{
}