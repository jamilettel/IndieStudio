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
    const std::string &text, const std::string &wn, s32 x, s32 y, s32 width, s32 height,
    bool drawBorder, bool dynamic) :
Component(e), windowName(wn), _text(text), _dimension(x, y, x + width, y + height), _drawBorder(drawBorder), _font(), _dynamic(dynamic)
{
}

is::components::TextComponent::TextComponent(std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text, const std::string &wn, s32 x, s32 y, s32 width, s32 height,
    bool drawBorder, const std::string &font, bool dynamic) :
Component(e), windowName(wn), _text(text), _dimension(x, y, x + width, y + height), _drawBorder(drawBorder), _font(font), _dynamic(dynamic)
{
}


void is::components::TextComponent::init(std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    element = ptr_window->canvas->addStaticText(std::wstring(_text.begin(), _text.end()).c_str(), _dimension, _drawBorder, true, 0, IDGenerator::getNewID());
    if (!element)
        throw is::exceptions::Exception("TextCompononent", "Could not create node from model");
    if (!_font.empty())
        element->setOverrideFont(ptr_window->canvas->getFont(_font.c_str()));
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
