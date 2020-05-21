/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include "Components/Button.hpp"
#include <utility>
#include "IDGenerator.hpp"

using namespace irr;

is::components::ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft
    ):
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _image(),
    _pressed(),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _clicked(false),
    _ft(std::move(ft))
{
}

is::components::ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft,
    std::string image,
    std::string pressed
    ):
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _image(std::move(image)),
    _pressed(std::move(pressed)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _clicked(false),
    _ft(std::move(ft))
{
}

is::components::ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string text,
    std::string wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft,
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
    _ft(std::move(ft))
{
}

void is::components::ButtonComponent::init(std::shared_ptr<is::components::WindowComponent> &ptr_window)
{
    _window = ptr_window;
    element = ptr_window->canvas->addButton(_dimension, nullptr, IDGenerator::getNewID(), std::wstring(_text.begin(), _text.end()).c_str());
    if (!element)
        throw is::exceptions::Exception("ButtonCompononent", "Could not create node from model");
    if (!_image.empty() && !_pressed.empty()) {
        element->setImage(ptr_window->driver->getTexture(_image.c_str()));
        element->setPressedImage(ptr_window->driver->getTexture(_pressed.c_str()));
        element->setScaleImage(true);
    }
    if (!_font.empty())
        element->setOverrideFont(ptr_window->canvas->getFont(_font.c_str()));
    element->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
    element->setUseAlphaChannel(true);
    element->setDrawBorder(false);
}

bool is::components::ButtonComponent::isClicked() const
{
    return _clicked;
}

void is::components::ButtonComponent::setClicked(bool clicked)
{
    _clicked = clicked;
}

s32 is::components::ButtonComponent::getId() const
{
    return element->getID();
}

void is::components::ButtonComponent::deleteComponent()
{
    element->remove();
}

void is::components::ButtonComponent::bringToFront()
{
    if (element)
        _window->canvas->getRootGUIElement()->bringToFront(element);
}

void is::components::ButtonComponent::setCallback(std::function<void()> ft)
{
    _ft = std::move(ft);
}

void is::components::ButtonComponent::callCallback() const
{
    _ft();
}

void is::components::ButtonComponent::setVisible(bool visible)
{
    element->setVisible(visible);
}
