/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Components/Bomb.hpp"

using namespace is::components;
using namespace is::ecs;

BombComponent::BombComponent(std::shared_ptr<Entity> &e,
    std::shared_ptr<BombermanComponent> &bm,
    const irr::core::vector3df &pos,
    float lt,
    int size
) : Component(e), lifeTime(lt), bombSize(size), bomberman(bm), _pos(pos)
{
}

void BombComponent::deleteComponent()
{
    
}
