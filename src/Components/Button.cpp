/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Button
*/

#include "Components/Button.hpp"

using namespace irr;

is::components::ButtonComponent::ButtonComponent(std::shared_ptr<is::ecs::Entity> &e,
    const std::string &text, const std::string &wn, s32 x, s32 y, s32 width, s32 height,
    void (*fct)()) :
Component(e), fctButton(fct), _clicked(false), _text(text), windowName(wn), _dimension(x, y, x + width, y + height)
{
}


void is::components::ButtonComponent::init(std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    element = ptr_window->canvas->addButton(_dimension, 0, -1, std::wstring(_text.begin(), _text.end()).c_str());
    if (!element)
        throw new is::exceptions::Exception("ButtonCompononent", "Could not create node from model");
}

bool is::components::ButtonComponent::isClicked() const
{
    return (_clicked);
}

void is::components::ButtonComponent::setClicked(bool clicked)
{
    _clicked = clicked;
}

s32 is::components::ButtonComponent::getId() const
{
    return (element->getID());
}

void is::components::ButtonComponent::deleteComponent()
{
    element->remove();
}
