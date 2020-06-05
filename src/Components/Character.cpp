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

int CharacterComponent::getTimePlaying() const noexcept
{
    return (_timePlaying);
}

int CharacterComponent::getNbBombPosed() const noexcept
{
    return (_nbBombPosed);
}

int CharacterComponent::getNbBonusCollected() const noexcept
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
    _stop = true;
    _position = 1;
    _time.value().get().resetStartTime();
}

void CharacterComponent::startTime() noexcept
{
    _stop = false;
    _timePlaying = 0;
    _time.value().get().resetStartTime();
    _time.value().get().start();
}

void CharacterComponent::stopTime() noexcept
{
    _stop = true;
}

void CharacterComponent::udpateTime()
{
    if (_stop || !_time.has_value())
        return;
    _time.value().get().update();
    _timePlaying += _time.value().get().getCurrentIntervalSeconds();
}

const std::string CharacterComponent::getTimeString() const noexcept
{
    return (std::string(
        (_timePlaying / 60 < 10 ? "0" : "" ) + 
        std::to_string(static_cast<int>(_timePlaying) / 60) + ":" + 
        (static_cast<int>(_timePlaying) % 60 < 10 ? "0" : "") + 
        std::to_string(static_cast<int>(_timePlaying) % 60)
    ));
}

void CharacterComponent::setTimeComponent(TimeComponent &time) noexcept
{
    _time.emplace(time);
}

void CharacterComponent::setPosition(int position) noexcept
{
    _position = position;
}

int CharacterComponent::getPosition() const noexcept
{
    return (_position);
}