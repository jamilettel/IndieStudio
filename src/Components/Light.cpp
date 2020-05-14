/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Light
*/

#include "Components/Light.hpp"

is::components::LightComponent::LightComponent(std::shared_ptr<is::ecs::Entity> &e,
                                               const std::string &window,
                                               const irr::core::vector3df& pos,
                                               irr::video::SColorf col,
                                               float rad) :
Component(e)
{
    radius = rad;
    position = pos;
    color = col;
    windowName = window;
}

void is::components::LightComponent::deleteComponent()
{
    
}