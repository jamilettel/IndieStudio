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
    _image(e->addComponent<ImageComponent>(
               e,
               RESOURCE("ui/Alert/Box.png"),
               "Indie Studio",
               WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 375,
               WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 230,
               true,
               false
               )),
    _button(e->addComponent<ButtonComponent>(
                e,
                "",
                "Indie Studio",
                WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 361 / 2,
                _image.getPosition().Y + 290,
                360, 101,
                [this] () {this->acceptAlert();},
                false,
                RESOURCE("ui/Alert/OkButton.png"),
                RESOURCE("ui/Alert/OkButtonPressed.png")
                )),
    _text(e->addComponent<TextComponent>(
              e,
              "test",
              "Indie Studio",
              WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350,
              WindowComponent::_windowsDimensions["Indie Studio"].second / 2 - 210,
              700, 260,
              false,
              true,
              RESOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
              irr::video::SColor(255, 255, 255, 255),
              false
              ))
{
    _image.layer = 5;
    _text.layer = 6;
    _button.layer = 6;
}

void AlertComponent::deleteComponent()
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
    _image.setVisible(false);
    _button.setVisible(false);
    _text.setVisible(false);
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
        _image.setVisible(true);
        _button.setVisible(true);
        _text.setVisible(true);
        _text.setText(_alert);
    }
}

ButtonComponent &AlertComponent::getButton() const noexcept
{
    return _button;
}
