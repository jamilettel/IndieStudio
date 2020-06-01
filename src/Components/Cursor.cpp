/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Cursor
*/

#include "Components/Cursor.hpp"

using namespace is::components;
using namespace is::ecs;

CursorComponent::CursorComponent(
    std::shared_ptr<Entity> &e,
    ImageComponent &cursorImage,
    WindowComponent &window,
    bool mouseCursor
    ):
    Component(e), _cursorImage(cursorImage), _window(window), isMouseCursor(mouseCursor)
{
}

void CursorComponent::deleteComponent()
{
}

const irr::core::vector2df &CursorComponent::getPosition() const noexcept
{
    return _pos;
}

void CursorComponent::move(float x, float y)
{
    _pos.X += x;
    _pos.Y += y;
}

void CursorComponent::setPosition(float x, float y)
{
    _pos.X = x;
    _pos.Y = y;
}

ImageComponent &CursorComponent::getImage() const noexcept
{
    return _cursorImage;
}

WindowComponent &CursorComponent::getWindow() const noexcept
{
    return _window;
}
