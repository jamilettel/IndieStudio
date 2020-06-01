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
    PowerUpComponent::PowerUpType tp) :
Component(e), type(tp)
{
}

void PowerUpComponent::deleteComponent()
{

}