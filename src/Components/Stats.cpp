/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Stats
*/

#include "Components/Stats.hpp"

using namespace is::ecs;
using namespace is::components;

StatsComponent::StatsComponent(
    std::shared_ptr<Entity> &e,
    TextComponent &highText,
    TextComponent &lowText,
    std::vector<std::pair<std::string, std::string>> stats
) : Component(e), _highText(highText), _lowText(lowText), _stats(std::move(stats))
{
}

StatsComponent::~StatsComponent()
= default;

void StatsComponent::next() noexcept
{
    _i++;
    if (_i == static_cast<int>(_stats.size()))
        _i = 0;
    _highText.setText(_stats[_i].first);
    _lowText.setText(_stats[_i].second);
}

void StatsComponent::prev() noexcept
{
    _i--;
    if (_i == -1)
        _i = static_cast<int>(_stats.size() - 1);
    _highText.setText(_stats[_i].first);
    _lowText.setText(_stats[_i].second);
}

void StatsComponent::deleteComponent()
{
}

void StatsComponent::setContinue(bool c) noexcept
{
    _continue = c;
}

bool StatsComponent::isContinue() const noexcept
{
    return (_continue);
}