/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Rules
*/

#include "Components/Rules.hpp"

using namespace is::components;

RulesComponent::RulesComponent(std::shared_ptr<is::ecs::Entity> &e) : Component(e)
{
    _icons[ACCELERATOR] = true;
    _icons[EXPLOSION] = true;
    _icons[BOMB] = true;
    _icons[WALL_PASS] = true;
}

void RulesComponent::deleteComponent()
{

}

bool RulesComponent::useIcon(Icon icon)
{
    return (_icons[icon]);
}

void RulesComponent::setIconUse(Icon icon, bool use) noexcept
{
    _icons[icon] = use;
}

void RulesComponent::setNumberOfPlayers(int nb) noexcept
{
    _numberOfPlayers = nb;
}

void RulesComponent::setFpsMode(bool mode) noexcept
{
    _fpsMode = mode;
}

void RulesComponent::setMaxTime(float time) noexcept
{
    _maxTime = time;
}
