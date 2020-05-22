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
    const std::string &text,
    const std::string &wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft
    ):
    GUIElementComponent(e),
    _ft(std::move(ft)),
    windowName(std::move(wn)),
    _clicked(false),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _image(),
    _pressed()
{
}

is::components::ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text,
    const std::string &wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft,
    const std::string &image,
    const std::string &pressed
    ):
    GUIElementComponent(e),
    _ft(std::move(ft)),
    windowName(std::move(wn)),
    _clicked(false),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _image(std::move(image)),
    _pressed(std::move(pressed))
{
}

is::components::ButtonComponent::ButtonComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text,
    const std::string &wn,
    s32 x,
    s32 y,
    s32 width,
    s32 height,
    std::function<void()> ft,
    const std::string &image,
    const std::string &pressed,
    const std::string &font
    ):
    GUIElementComponent(e),
    _ft(std::move(ft)),
    windowName(std::move(wn)),
    _clicked(false),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _image(std::move(image)),
    _pressed(std::move(pressed)),
    _font(std::move(font))
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
    if (element)
        return element->getID();
    return (-1);
}

void is::components::ButtonComponent::deleteComponent()
{
    if (element)
        element->remove();
    element = nullptr;
}

void is::components::ButtonComponent::bringToFront()
{
    if (element)
        _window->canvas->getRootGUIElement()->bringToFront(element);
}
