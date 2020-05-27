/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RulesSettingComponent
*/

#include "Components/RulesSetting.hpp"

using namespace is::components;
using namespace is::ecs;

RulesSettingComponent::RulesSettingComponent(std::shared_ptr<is::ecs::Entity> &e) : Component(e)
{
}

void RulesSettingComponent::addRule(std::function<void()> onSelect, std::function<void()> onExit)
{
    _rules.emplace_back(std::make_pair(onSelect, onExit));
}

void RulesSettingComponent::up()
{
    if (_rules.size() == 0)
        return;
    _rules[_i].second();
    _i++;
    if (_i == _rules.size())
        _i = 0;
    _rules[_i].first();
}

void RulesSettingComponent::down()
{
    if (_rules.size() == 0)
        return;
    _rules[_i].second();
    _i--;
    if (_i == -1)
        _i = _rules.size() - 1;
    _rules[_i].first();
}

int RulesSettingComponent::getIndex() const noexcept
{
    return (_i);
}

void RulesSettingComponent::deleteComponent()
{

}