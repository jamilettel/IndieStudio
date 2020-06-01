/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Timer
*/

#include "Components/Timer.hpp"

using namespace is::components;
using namespace is::ecs;

TimerComponent::TimerComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    TextComponent &text,
    TimeComponent &timeComponent,
    float time
) : Component(e), _text(text), _timeC(timeComponent), _time(time)
{
}

void TimerComponent::deleteComponent()
{
}

void TimerComponent::update()
{
    _time -= _timeC.getCurrentIntervalSeconds();
    _text.setText(
        (_time / 60 < 10 ? "0" : "" ) + 
        std::to_string(static_cast<int>(_time) / 60) + ":" + 
        (static_cast<int>(_time) % 60 < 10 ? "0" : "") + 
        std::to_string(static_cast<int>(_time) % 60)
    );
}