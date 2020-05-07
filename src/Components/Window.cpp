/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "Components/Window.hpp"

is::components::WindowComponent::WindowComponent(std::shared_ptr<is::ecs::Entity> &e,
                                                 const std::string &wn,
                                                 irr::core::dimension2d<u32> ws,
                                                 bool fs) :
Component(e)
{
    windowName = wn;
    windowSize = ws;
    fullscreen = fs;
}

void is::components::WindowComponent::deleteComponent()
{
    
}