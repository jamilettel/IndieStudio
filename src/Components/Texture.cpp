/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Texture
*/

#include "Components/Texture.hpp"

#include "Exception.hpp"

is::components::TextureComponent::TextureComponent(std::shared_ptr<is::ecs::Entity> &e,
                                                               const std::string &name,
                                                               const std::string &window) :
Component(e)
{
    filename = name;
    windowName = window;
}

void is::components::TextureComponent::init(std::shared_ptr<is::components::WindowComponent> &ptrWindow)
{
    node = ptrWindow->driver->getTexture(filename.c_str());
    if (!node)
        throw is::exceptions::Exception("TextureComponent", "Could not create node from model");
    ptrWindow->driver->makeColorKeyTexture(node, core::position2d<s32>(0,0));
}

void is::components::TextureComponent::deleteComponent()
{
    node->drop();
}
