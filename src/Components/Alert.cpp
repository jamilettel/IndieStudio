/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Alert
*/

#include "Components/Alert.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#ifndef RESOURCE
#define RESOURCE(str) RESOURCES_PATH str
#endif

using namespace is::components;
using namespace is::ecs;

AlertComponent::AlertComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e),
    _image(e->addComponent<ImageComponent>(e, RESOURCE("ui/Alert/Box.png"), "Indie Studio", 0, 0)),
    _button(e->addComponent<ButtonComponent>(
                e,
                "Ok",
                "Indie Studio",
                0, 0,
                360, 101,
                [this] () {acceptAlert();},
                false,
                RESOURCE("ui/Alert/OkButton.png"),
                RESOURCE("ui/Alert/OkButtonPressed.png")
                ))
{
    _image.setVisible(false);
}

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
    _image.setVisible(false);
    _button.setVisible(false);
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
