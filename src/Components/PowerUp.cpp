/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUp
*/

#include "Components/PowerUp.hpp"

is::components::PowerUpComponent::PowerUpComponent(std::shared_ptr<is::ecs::Entity> &e,
    is::components::PowerUpComponent::PowerUpType tp) :
Component(e)
{
    type = tp;
}

void is::components::PowerUpComponent::deleteComponent()
{

}