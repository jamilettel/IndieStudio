/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Hud
*/

#include "Components/Hud.hpp"

using namespace is::components;
using namespace is::ecs;

HudComponent::HudComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    BombermanComponent &bm,
    TextComponent &bombNb,
    TextComponent &range,
    TextComponent &speed,
    TextComponent &pass
) : Component(e), _bm(bm), _bombNb(bombNb), _range(range), _speed(speed), _pass(pass)
{
}

void HudComponent::deleteComponent()
{
}

void HudComponent::update()
{
    _bombNb.setText("x " + std::to_string(_bm.bombNumber - 1));
    _range.setText ("x " + std::to_string(_bm.bombRange - 1));
    _speed.setText ("x " + std::to_string(_bm.speedCount));
    _pass.setText  (std::string(_bm.wallPass ? "yes" : "no"));
}
