/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "Components/Window.hpp"

std::map<std::string, std::pair<int, int>> is::components::WindowComponent::_windowsDimensions;

int is::components::WindowComponent::_width = 0;
int is::components::WindowComponent::_height = 0;

is::components::WindowComponent::WindowComponent(std::shared_ptr<is::ecs::Entity> &e,
                                                 const std::string &wn,
                                                 irr::core::dimension2d<u32> ws,
                                                 bool fs) :
Component(e)
{
    windowName = wn;
    windowSize = ws;
    fullscreen = fs;
    _width = ws.Width;
    _height = ws.Height;
    _windowsDimensions[wn] = std::pair<int, int>(_width, _height);
}

void is::components::WindowComponent::deleteComponent()
{
    
}
