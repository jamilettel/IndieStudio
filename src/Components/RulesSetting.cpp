/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RulesSettingComponent
*/

#include "Components/RulesSetting.hpp"

using namespace is::ecs;
using namespace is::components;

RulesSettingComponent::RulesSettingComponent(std::shared_ptr<Entity> &e) : Component(e)
{
}

void RulesSettingComponent::addRule(
    const std::function<void()>& onSelect,
    const std::function<void()>& onExit,
    const std::function<void()>& onDisappear,
    const std::function<void()>& onRuleUp,
    const std::function<void()>& onRuleDown,
    const std::function<void()>& onAppear
)
{
    if (_first + 4 != _last + 1)
        _last++;
    _rules.emplace_back(std::make_tuple(onSelect, onExit, onDisappear, onRuleUp, onRuleDown, onAppear));
}

void RulesSettingComponent::up()
{
    if (_rules.empty())
        return;
    if (_i + 1 == _rules.size())
        return;
    std::get<1>(_rules[_i])();
    _i++;
    if (_i > _last) {
        int j = 0;
        _last++;
        _first++;
        std::for_each(_rules.begin(), _rules.end(), [this, &j](auto &rule) {
            if (j < this->getFirst() || j > this->getLast())
                std::get<2>(rule)();
            else
                std::get<5>(rule)();
            std::get<3>(rule)();
            j++;
        });
    }
    std::get<0>(_rules[_i])();
}

void RulesSettingComponent::down()
{
    if (_rules.empty())
        return;
    if (_i - 1 == -1)
        return;
    std::get<1>(_rules[_i])();
    _i--;
    if (_i < _first) {
        int j = 0;
        _last--;
        _first--;
        std::for_each(_rules.begin(), _rules.end(), [this, &j](auto &rule) {
            if (j < this->getFirst() || j > this->getLast())
                std::get<2>(rule)();
            else
                std::get<5>(rule)();
            std::get<4>(rule)();
            j++;
        });
    }
    std::get<0>(_rules[_i])();
}

int RulesSettingComponent::getIndex() const noexcept
{
    return _i;
}

void RulesSettingComponent::deleteComponent()
{

}

int RulesSettingComponent::getFirst() const noexcept
{
    return _first;
}

int RulesSettingComponent::getLast() const noexcept
{
    return _last;
}
