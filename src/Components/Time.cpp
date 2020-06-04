/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Time Component
*/

#include "Components/Time.hpp"

using namespace is::ecs;
using namespace is::components;

TimeComponent::TimeComponent(std::shared_ptr<Entity> &e) : Component(e), _elapsed_time(0.0), _interval_milliseconds(0.0), _interval_seconds(0.0)
{
}

void TimeComponent::start()
{
    _begin = std::chrono::system_clock::now();
    _start = std::chrono::system_clock::now();
}

void TimeComponent::update()
{
    _end = std::chrono::system_clock::now();
    _elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(_end - _begin).count() / 1000.0;
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

float TimeComponent::getElapsedTime() const
{
    return _elapsed_time;
}

void TimeComponent::resetStartTime()
{
    _begin = std::chrono::system_clock::now();
}

