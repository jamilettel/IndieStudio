/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include <utility>
#include "Components/Button.hpp"
#include "IDGenerator.hpp"
#include "Game.hpp"

using namespace is::components;
using namespace is::ecs;

ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    irr::s32 x,
    irr::s32 y,
    irr::s32 width,
    irr::s32 height,
    std::function<void()> ft,
    bool visible
    ):
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _image(),
    _pressed(),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _clicked(false),
    _visible(visible),
    _ft(std::move(ft))
{
}

ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    irr::s32 x,
    irr::s32 y,
    irr::s32 width,
    irr::s32 height,
    std::function<void()> ft,
    bool visible,
    std::string image,
    std::string pressed
) :
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _image(std::move(image)),
    _pressed(std::move(pressed)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _clicked(false),
    _visible(visible),
    _ft(std::move(ft))
{
}

ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    irr::s32 x,
    irr::s32 y,
    irr::s32 width,
    irr::s32 height,
    std::function<void()> ft,
    bool visible,
    std::string image,
    std::string pressed,
    std::string font
):
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _image(std::move(image)),
    _pressed(std::move(pressed)),
    _font(std::move(font)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _clicked(false),
    _visible(visible),
    _ft(std::move(ft))
{
}

void ButtonComponent::init(std::shared_ptr<WindowComponent> &ptr_window)
{
    _window = ptr_window;
    element = ptr_window->canvas->addButton(_dimension, nullptr, IDGenerator::getNewID(), std::wstring(_text.begin(), _text.end()).c_str());
    if (!element)
        throw is::exceptions::Exception("ButtonCompononent", "Could not create node from model");
    if (!_image.empty() && !_pressed.empty()) {
        element->setImage(static_cast<irr::video::ITexture *>(is::Game::getResource(_image)));
        element->setPressedImage(static_cast<irr::video::ITexture *>(is::Game::getResource(_pressed)));
        element->setScaleImage(true);
    }
    if (!_font.empty())
        element->setOverrideFont(static_cast<irr::gui::IGUIFont *>(is::Game::getResource(_font)));
    element->setAlignment(irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE, irr::gui::EGUIA_SCALE);
    element->setUseAlphaChannel(true);
    element->setDrawBorder(false);
    element->setVisible(_visible);
}

bool ButtonComponent::isClicked() const
{
    return _clicked;
}

void ButtonComponent::setClicked(bool clicked)
{
    _clicked = clicked;
}

irr::s32 ButtonComponent::getId() const
{
    if (element)
        return element->getID();
    return (-1);
}

void ButtonComponent::deleteComponent()
{
    if (element)
        element->remove();
    element = nullptr;
}

void ButtonComponent::bringToFront()
{
    if (element)
        _window->canvas->getRootGUIElement()->bringToFront(element);
}

void ButtonComponent::setCallback(std::function<void()> ft)
{
    _ft = std::move(ft);
}

void ButtonComponent::callCallback(int callerId)
{
    if (isDisabled())
        return;
    _callerId = callerId;
    _ft();
}

int ButtonComponent::getCallerId() const
{
    return _callerId;
}

void ButtonComponent::setVisible(bool visible)
{
    if (_visible != visible) {
        _visible = visible;
        element->setVisible(visible);
    }
}

void ButtonComponent::setDisabled(bool disabled) noexcept
{
    if (disabled)
        _disabled++;
    else if (_disabled > 0)
        _disabled--;
}

bool ButtonComponent::isDisabled() const noexcept
{
    return _disabled > 0;
}

bool ButtonComponent::contains(const irr::core::vector2df &pos) const
{
    if (!_visible)
        return false;
    return _dimension.isPointInside(irr::core::vector2di(pos.X, pos.Y));
}
