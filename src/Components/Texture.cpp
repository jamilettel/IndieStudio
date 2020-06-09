/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Texture
*/

#include "Components/Texture.hpp"
#include "Exception.hpp"
#include "Game.hpp"

using namespace is::ecs;
using namespace is::components;

TextureComponent::TextureComponent(
    std::shared_ptr<Entity> &e,
    std::string name,
    std::string window,
    const irr::core::vector2df &pos,
    const irr::core::vector2df &size,
    bool visible
) : Component(e), filename(std::move(name)), windowName(std::move(window)), _pos(pos), _size(size), _visible(visible)
{
}

void TextureComponent::init(std::shared_ptr<WindowComponent> &ptrWindow)
{
    _node = static_cast<irr::video::ITexture *>(is::Game::getResource(filename));
    if (!_node)
        throw is::exceptions::Exception("TextureComponent", "Could not create node from model");
    ptrWindow->driver->makeColorKeyTexture(_node, irr::core::position2d<irr::s32>(0,0));
}

void TextureComponent::deleteComponent()
{
}

const irr::core::vector2df &TextureComponent::getPosition() const noexcept
{
    return _pos;
}

const irr::core::vector2df &TextureComponent::getSize() const noexcept
{
    return _size;
}

irr::video::ITexture *TextureComponent::getNode() const noexcept
{
    return _node;
}

bool TextureComponent::isVisible() const noexcept
{
    return _visible;
}

void TextureComponent::setVisible(bool visible) noexcept
{
    _visible = visible;
}

void TextureComponent::setPosition(const irr::core::vector2df &position) noexcept
{
    _pos = position;
}
