/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Light
*/

#include "Components/Light.hpp"

using namespace is::ecs;
using namespace is::components;

LightComponent::LightComponent(std::shared_ptr<Entity> &e,
                               std::string window,
                               const irr::core::vector3df& pos,
                               irr::video::SColorf col,
                               float rad) :
Component(e), windowName(std::move(window)), position(pos), color(col), radius(rad)
{
}

void LightComponent::deleteComponent()
{
}
