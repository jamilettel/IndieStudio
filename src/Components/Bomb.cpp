/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Components/Bomb.hpp"

is::components::BombComponent::BombComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{
    lifeTime = 3;
}
