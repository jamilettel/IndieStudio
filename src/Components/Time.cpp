/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "Components/Time.hpp"

using namespace is::components;

TimeComponent::TimeComponent(std::shared_ptr<is::ecs::Entity> &e) : Component(e), _interval_milliseconds(0.0), _interval_seconds(0.0)
{
}

void TimeComponent::start()
{
    _start = std::chrono::system_clock::now();
}

void TimeComponent::setCurrentInterval()
{
    _end = std::chrono::system_clock::now();
    _interval_milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count() / 1000.0;
    _interval_seconds =_interval_milliseconds / 1000.0;
    _start = std::chrono::system_clock::now();
}

float TimeComponent::getCurrentIntervalSeconds() const
{
    return _interval_seconds;
}

float TimeComponent::getCurrentIntervalMilliseconds() const
{
    return _interval_milliseconds;
}

void TimeComponent::deleteComponent()
{
}

