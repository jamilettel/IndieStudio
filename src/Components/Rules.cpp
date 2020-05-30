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

int RulesComponent::getNumberOfPlayers() const noexcept
{
    return (_numberOfPlayers);
}

float RulesComponent::getMaxTime() const noexcept
{
    return (_maxTime);
}

bool RulesComponent::isFpsMode() const noexcept
{
    return (_fpsMode);
}

bool RulesComponent::noIconUsed() const noexcept
{
    for (const auto &icon : _icons) {
        if (icon.second == true)
            return (false);
    }
    return (true);
}

void RulesComponent::setAllICons(bool used) noexcept
{
    _icons[ACCELERATOR] = used;
    _icons[EXPLOSION] = used;
    _icons[BOMB] = used;
    _icons[WALL_PASS] = used;
}

std::string RulesComponent::getTimeString() const
{
    return (std::string(
        (_maxTime / 60 < 10 ? "0" : "" ) + 
        std::to_string(static_cast<int>(_maxTime) / 60) + ":" + 
        (static_cast<int>(_maxTime) % 60 < 10 ? "0" : "") + 
        std::to_string(static_cast<int>(_maxTime) % 60)
    ));
}