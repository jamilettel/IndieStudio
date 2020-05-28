/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "Components/Window.hpp"

using namespace is::components;

std::map<std::string, std::pair<int, int>> WindowComponent::_windowsDimensions;

int WindowComponent::_width = 0;
int WindowComponent::_height = 0;

WindowComponent::WindowComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    const std::string &wn,
    irr::core::dimension2d<u32> ws,
    bool fs
    ):
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
{}
