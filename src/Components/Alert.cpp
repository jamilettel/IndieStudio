/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Alert
*/

#include "Components/Alert.hpp"

using namespace is::components;
using namespace is::ecs;

AlertComponent::AlertComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e)
{}

const std::string &AlertComponent::getCurrentAlert() const
{
    return _alert;
}

size_t AlertComponent::getQueueLength() const
{
    return _queue.size();
}

void AlertComponent::addAlert(const std::string &alert)
{
    _queue.emplace_back(alert);
}

void AlertComponent::acceptAlert()
{
    _hasAlert = false;
}

bool AlertComponent::hasAlert() const
{
    return _hasAlert;
}

void AlertComponent::setNextAlert()
{
    if (_queue.size() && !_hasAlert) {
        _hasAlert = true;
        _alert = _queue[0];
        _queue.erase(_queue.begin());
    }
}
