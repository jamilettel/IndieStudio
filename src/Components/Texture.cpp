/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Texture
*/

#include "Components/Texture.hpp"

#include "Exception.hpp"

is::components::TextureComponent::TextureComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    const std::string &name,
    const std::string &window,
    const irr::core::vector2df &pos,
    const irr::core::vector2df &size,
    bool visible
) : Component(e), filename(name), windowName(window), _pos(pos), _size(size), _visible(visible)
{
}

void is::components::TextureComponent::init(std::shared_ptr<is::components::WindowComponent> &ptrWindow)
{
    _node = ptrWindow->driver->getTexture(filename.c_str());
    if (!_node)
        throw is::exceptions::Exception("TextureComponent", "Could not create node from model");
    ptrWindow->driver->makeColorKeyTexture(_node, core::position2d<s32>(0,0));
}

void is::components::TextureComponent::deleteComponent()
{
}

const irr::core::vector2df &is::components::TextureComponent::getPosition() const noexcept
{
    return (_pos);
}

const irr::core::vector2df &is::components::TextureComponent::getSize() const noexcept
{
    return (_size);
}

irr::video::ITexture *is::components::TextureComponent::getNode() const noexcept
{
    return (_node);
}

bool is::components::TextureComponent::isVisible() const noexcept
{
    return (_visible);
}

void is::components::TextureComponent::setVisible(bool visible) noexcept
{
    _visible = visible;
}