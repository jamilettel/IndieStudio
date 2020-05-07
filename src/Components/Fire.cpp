/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#include "Components/Fire.hpp"

is::components::FireComponent::FireComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{
    lifeTime = 3;
}
