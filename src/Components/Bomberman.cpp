/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomberman
*/

#include "Components/Bomberman.hpp"

is::components::BombermanComponent::BombermanComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{
    instantBomb = 0;

    bombRange = 1;
    bombNumber = 1;
    speedMult = 1;
    wallPass = false;
    dead = false;
    deathTimer = 0.7f;
}

void is::components::BombermanComponent::deleteComponent()
{
    
}