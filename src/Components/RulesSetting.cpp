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

void RulesSettingComponent::addRule(
    std::function<void()> onSelect,
    std::function<void()> onExit,
    std::function<void()> onDisappear,
    std::function<void()> onRuleUp,
    std::function<void()> onRuleDown,
    std::function<void()> onAppear
)
{
    if (_first + 4 != _last + 1)
        _last++;
    _rules.emplace_back(std::make_tuple(onSelect, onExit, onDisappear, onRuleUp, onRuleDown, onAppear));
}

void RulesSettingComponent::up()
{
    if (_rules.size() == 0)
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
    if (_rules.size() == 0)
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
    return (_i);
}

void RulesSettingComponent::deleteComponent()
{

}

int RulesSettingComponent::getFirst() const noexcept
{
    return (_first);
}

int RulesSettingComponent::getLast() const noexcept
{
    return (_last);
}
