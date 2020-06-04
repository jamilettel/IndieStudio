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

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#ifndef RESOURCE
#define RESOURCE(str) RESOURCES_PATH str
#endif

NumberComponent::NumberComponent(
    std::shared_ptr<Entity> &e
    ):
    ecs::Component(e)
{
    for (int i = 0; i < 5; i++) {
        _buttonDown.emplace_back(nullptr);
        _buttonUp.emplace_back(nullptr);
        _image.emplace_back(nullptr);
        _text.emplace_back(nullptr);
    }
    initOneComponent(e, _buttonDown[0], _buttonUp[0], _image[0], _text[0], 0);
    initOneComponent(e, _buttonDown[1], _buttonUp[1], _image[1], _text[1], 1);
    initOneComponent(e, _buttonDown[2], _buttonUp[2], _image[2], _text[2], 2);
    initOneComponent(e, _buttonDown[3], _buttonUp[3], _image[3], _text[3], 3);
    initOneComponent(e, _buttonDown[4], _buttonUp[4], _image[4], _text[4], 4);
}

void NumberComponent::deleteComponent()
{}

int NumberComponent::getEnteredNumber() const
{
    int nb = 0;

    for (int i = 0; i < 5; i++) {
        nb *= 10;
        nb += _numbers[i];
    }
    return 0;
}

void NumberComponent::changeNumber(int pos, int amount)
{
    _numbers[pos] += amount;
    if (_numbers[pos] < 0)
        _numbers[pos] = 9;
    else if (_numbers[pos] > 9)
        _numbers[pos] = 0;
    _text[pos]->setText(std::to_string(_numbers[pos]));
}

void NumberComponent::initOneComponent(
    std::shared_ptr<Entity> &e,
    ButtonComponent *&buttonDown,
    ButtonComponent *&buttonUp,
    ImageComponent *&image,
    TextComponent *&text,
    int num)
{
    buttonDown = &e->addComponent<ButtonComponent>(
        e,
        "", "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / (5 - num) - 105,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 + 200,
        210, 210,
        [this, num] () {changeNumber(num, -1);},
        false,
        RESOURCE("ui/Multiplayer/down_btn.png"),
        RESOURCE("ui/Multiplayer/down_btn_pressed.png")
        );
    buttonUp = &e->addComponent<ButtonComponent>(
        e,
        "", "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / (5 - num) - 105,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 200,
        210, 210,
        [this, num] () {changeNumber(num, 1);},
        false,
        RESOURCE("ui/Multiplayer/up_btn.png"),
        RESOURCE("ui/Multiplayer/up_btn_pressed.png")
        );
    image = &e->addComponent<ImageComponent>(
        e,
        RESOURCE("ui/Multiplayer/number_frame.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / (5 - num) - 192,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 250
        );
    text = &e->addComponent<TextComponent>(
        e,
        "0",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / (5 - num) - 192,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 250,
        384,
        500,
        false,
        true,
        RESOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        false
        );
}
