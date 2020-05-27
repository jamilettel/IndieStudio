/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Components/Bomb.hpp"

is::components::BombComponent::BombComponent(std::shared_ptr<is::ecs::Entity> &e,
    std::shared_ptr<is::components::BombermanComponent> &bm,
    const irr::core::vector3df &pos,
    float lt,
    int size
) : Component(e), _pos(pos)
{
    lifeTime = lt;
    bombSize = size;
    bomberman = bm;
}

void is::components::BombComponent::deleteComponent()
{
    
}
