/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#include "Components/Fire.hpp"

is::components::FireComponent::FireComponent(std::shared_ptr<is::ecs::Entity> &e, float lt) :
Component(e)
{
    lifeTime = lt;
}

void is::components::FireComponent::deleteComponent()
{
    
}
