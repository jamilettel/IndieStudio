/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Stats
*/

#include "Components/Stats.hpp"

using namespace is::components;

StatsComponent::StatsComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    TextComponent &highText,
    TextComponent &lowText,
    const std::vector<std::pair<std::string, std::string>> &stats
) : Component(e), _highText(highText), _lowText(lowText), _stats(stats)
{
}

StatsComponent::~StatsComponent()
{
}

void StatsComponent::next() noexcept
{
    _i++;
    if (_i == _stats.size())
        _i = 0;
    _highText.setText(_stats[_i].first);
    _lowText.setText(_stats[_i].second);
}

void StatsComponent::prev() noexcept
{
    _i--;
    if (_i == -1)
        _i = _stats.size() - 1;
    _highText.setText(_stats[_i].first);
    _lowText.setText(_stats[_i].second);
}

void StatsComponent::deleteComponent()
{
}