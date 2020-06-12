/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUp
*/

#include "Components/PowerUp.hpp"

using namespace is::ecs;
using namespace is::components;

PowerUpComponent::PowerUpComponent(std::shared_ptr<Entity> &e,
    PowerUpComponent::PowerUpType tp, AudioComponent &audio) :
Component(e), type(tp), _audio(audio)
{
}

void PowerUpComponent::deleteComponent()
{

}

AudioComponent &PowerUpComponent::getAudio() const noexcept
{
    return (_audio);
}