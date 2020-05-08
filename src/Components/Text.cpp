/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Text
*/

#include "Components/Text.hpp"

using namespace irr;


is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text, const std::string &wn, s32 x, s32 y, s32 width, s32 height,
    bool drawBorder) :
Component(e), windowName(wn), _text(text), _dimension(x, y, x + width, y + height), _drawBorder(drawBorder), _font()
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text, const std::string &wn, s32 x, s32 y, s32 width, s32 height,
    bool drawBorder, const std::string &font) :
Component(e), windowName(wn), _text(text), _dimension(x, y, x + width, y + height), _drawBorder(drawBorder), _font(font)
{
}


void is::components::TextComponent::init(std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    element = ptr_window->canvas->addStaticText(std::wstring(_text.begin(), _text.end()).c_str(), _dimension, _drawBorder, true, 0, -1);
    if (!element)
        throw new is::exceptions::Exception("TextCompononent", "Could not create node from model");
    if (!_font.empty())
        element->setOverrideFont(ptr_window->canvas->getFont(_font.c_str()));
}

void is::components::TextComponent::deleteComponent()
{
    element->remove();
}
