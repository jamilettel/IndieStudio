/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** NumberField
*/

#include "Components/NumberField.hpp"
#include "ECS/Entity.hpp"

using namespace is::components;
using namespace is::ecs;

NumberFieldComponent::NumberFieldComponent(
    std::shared_ptr<Entity> &e
    ):
    ecs::Component(e)
{
    for (int i = 0; i < 5; i++) {
        _buttonDown.emplace_back(nullptr);
        _buttonUp.emplace_back(nullptr);
        _image.emplace_back(nullptr);
        _text.emplace_back(nullptr);
        _numbers.emplace_back(0);
    }
    initOneComponent(e, 0);
    initOneComponent(e, 1);
    initOneComponent(e, 2);
    initOneComponent(e, 3);
    initOneComponent(e, 4);
}

void NumberFieldComponent::deleteComponent()
{}

int NumberFieldComponent::getEnteredNumber() const
{
    int nb = 0;

    for (int i = 0; i < 5; i++) {
        nb *= 10;
        nb += _numbers[i];
    }
    return nb;
}

void NumberFieldComponent::changeNumber(int pos, int amount)
{
    _numbers[pos] += amount;
    if (_numbers[pos] < 0)
        _numbers[pos] = 9;
    else if (_numbers[pos] > 9)
        _numbers[pos] = 0;
    _text[pos]->setText(std::to_string(_numbers[pos]));
}

void NumberFieldComponent::initOneComponent(
    std::shared_ptr<Entity> &e,
    int num)
{
    _buttonDown[num] = &e->addComponent<ButtonComponent>(
        e,
        "", "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 14 * (num + 5) - 25,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 + 60,
        50, 50,
        [this, num] () {changeNumber(num, -1);},
        true,
        "ui/Multiplayer/down_btn.png",
        "ui/Multiplayer/down_btn_pressed.png"
        );
    _buttonDown[num]->layer = 5;
    _buttonUp[num] = &e->addComponent<ButtonComponent>(
        e,
        "", "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 14 * (num + 5) - 25,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 110,
        50, 50,
        [this, num] () {changeNumber(num, 1);},
        true,
        "ui/Multiplayer/up_btn.png",
        "ui/Multiplayer/up_btn_pressed.png"
        );
    _buttonUp[num]->layer = 5;
    _image[num] = &e->addComponent<ImageComponent>(
        e,
        "ui/Multiplayer/number_frame.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 14 * (num + 5) - 38,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 50
        );
    _image[num]->layer = 5;
    _text[num] = &e->addComponent<TextComponent>(
        e,
        "0",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 14 * (num + 5) - 38,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 50,
        77,
        100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 255, 255, 255)
        );
    _text[num]->layer = 6;
}
