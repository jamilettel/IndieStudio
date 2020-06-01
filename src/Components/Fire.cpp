/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#include "Components/Fire.hpp"

using namespace is::components;
using namespace is::ecs;

FireComponent::FireComponent(std::shared_ptr<Entity> &e, float lt) :
Component(e), lifeTime(lt)
{
}

void FireComponent::deleteComponent()
{
    
}
