/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Text
*/

#include "Components/Text.hpp"
#include "IDGenerator.hpp"

using namespace irr;

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
std::string text, std::string wn, s32 x, s32 y, s32 width, s32 height,
bool drawBorder, bool dynamic, bool visible) :
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _dimension(x, y, x + width, y + height),
    _text(std::move(text)),
    _font(),
    _color(irr::video::SColor(0, 0, 0, 1)),
    _drawBorder(drawBorder),
    _dynamic(dynamic),
    _visible(visible)
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
std::string text, std::string wn, s32 x, s32 y, s32 width, s32 height,
bool drawBorder, bool dynamic, std::string font, bool visible) :
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _dimension(x, y, x + width, y + height),
    _text(std::move(text)),
    _font(std::move(font)),
    _color(irr::video::SColor(0, 0, 0, 1)),
    _drawBorder(drawBorder),
    _dynamic(dynamic),
    _visible(visible)
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
std::string text, std::string wn, s32 x, s32 y, s32 width, s32 height,
bool drawBorder, bool dynamic, std::string font, irr::video::SColor color, bool visible) :
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _dimension(x, y, x + width, y + height),
    _text(std::move(text)),
    _font(std::move(font)),
    _color(color),
    _drawBorder(drawBorder),
    _dynamic(dynamic),
    _visible(visible)
{
}

void is::components::TextComponent::init(std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    _window = ptr_window;
    element = ptr_window->canvas->addStaticText(std::wstring(_text.begin(), _text.end()).c_str(), _dimension, _drawBorder, true, 0, IDGenerator::getNewID());
    if (!element)
        throw is::exceptions::Exception("TextCompononent", "Could not create node from model");
    if (!_font.empty())
        element->setOverrideFont(ptr_window->canvas->getFont(_font.c_str()));
    element->setOverrideColor(_color);
    element->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
    element->setTextAlignment(gui::EGUIA_CENTER, gui::EGUIA_CENTER);
    element->setVisible(_visible);
}

std::string is::components::TextComponent::getText() const
{
    return (_text);
}

void is::components::TextComponent::setText(const std::string &text)
{
    _text = text;
    element->setText(std::wstring(_text.begin(), _text.end()).c_str());
}

void is::components::TextComponent::updateText()
{
    if (!_dynamic)
        return;
    element->setText(std::wstring(_text.begin(), _text.end()).c_str());
}

void is::components::TextComponent::deleteComponent()
{
    element->remove();
}

void is::components::TextComponent::bringToFront()
{
    if (element)
        _window->canvas->getRootGUIElement()->bringToFront(element);
}

void is::components::TextComponent::setVisible(bool visible)
{
    _visible = visible;
    element->setVisible(visible);
}

void is::components::TextComponent::move(const irr::core::vector2di &pos) noexcept
{
    element->move(pos);
}
