/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#include "Components/Character.hpp"

using namespace is::components;
using namespace is::ecs;

CharacterComponent::CharacterComponent(
    std::shared_ptr<Entity> &e,
    int characterNumber,
    std::string texture
) : Component(e), number(characterNumber), texturePath(std::move(texture))
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

size_t CharacterComponent::getTimePlaying() const noexcept
{
    return (_timePlaying);
}

size_t CharacterComponent::getNbBombPosed() const noexcept
{
    return (_nbBombPosed);
}

size_t CharacterComponent::getNbBonueCollected() const noexcept
{
    return (_nbBonusCollected);
}

size_t CharacterComponent::getNbCharactersKilled() const noexcept
{
    return (_nbCharactersKilled);
}

void CharacterComponent::deleteComponent()
{
}

bool CharacterComponent::isAI() const noexcept
{
    return (characterType == Type::AI);
}

void CharacterComponent::reset() noexcept
{
    _timePlaying = 0;
    _nbBombPosed = 0;
    _nbBonusCollected = 0;
    _nbCharactersKilled = 0;
}