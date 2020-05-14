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
bool drawBorder, bool dynamic) :
    Component(e),
    windowName(std::move(wn)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _drawBorder(drawBorder),
    _font(),
    _dynamic(dynamic),
    _color(irr::video::SColor(0, 0, 0, 1))
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
std::string text, std::string wn, s32 x, s32 y, s32 width, s32 height,
bool drawBorder, bool dynamic, std::string font) :
    Component(e),
    windowName(std::move(wn)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _drawBorder(drawBorder),
    _font(std::move(font)),
    _dynamic(dynamic),
    _color(irr::video::SColor(0, 0, 0, 1))
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
std::string text, std::string wn, s32 x, s32 y, s32 width, s32 height,
bool drawBorder, bool dynamic, std::string font, irr::video::SColor color) :
    Component(e),
    windowName(std::move(wn)),
    _text(std::move(text)),
    _dimension(x, y, x + width, y + height),
    _drawBorder(drawBorder),
    _font(std::move(font)),
    _dynamic(dynamic),
    _color(color)
{
}

void is::components::TextComponent::init(const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    element = ptr_window->canvas->addStaticText(std::wstring(_text.begin(), _text.end()).c_str(), _dimension, _drawBorder, true, 0, IDGenerator::getNewID());
    if (!element)
        throw is::exceptions::Exception("TextCompononent", "Could not create node from model");
    if (!_font.empty())
        element->setOverrideFont(ptr_window->canvas->getFont(_font.c_str()));
    element->setOverrideColor(_color);
    element->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
}

std::string is::components::TextComponent::getText() const
{
    return (_text);
}

void is::components::TextComponent::setText(const std::string &text)
{
    _text = text;
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
