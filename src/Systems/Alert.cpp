/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Alert
*/

#include "Systems/Alert.hpp"

using namespace is::components;
using namespace is::systems;
using namespace is::ecs;

void AlertSystem::awake()
{}

void AlertSystem::start()
{
}

void AlertSystem::update()
{
    auto &alerts = _componentManager->getComponentsByType(typeid(AlertComponent).hash_code());

    if (!alerts.size())
        return;

    auto ptr = static_cast<AlertComponent*>(alerts[0].get());

    if (ptr->getQueueLength() && !ptr->hasAlert()) {
        ptr->setNextAlert();
        if (!_disabledButtons.size()) {
            _disabledButtons = _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code());
            setDisabledButtons(true, ptr->getButton());
        }
    } else if (_disabledButtons.size() && !ptr->hasAlert()) {
        setDisabledButtons(false, ptr->getButton());
        _disabledButtons.clear();
    } else {
        static size_t i = 0;

        if (i<3u)
            ptr->addAlert("OK " + std::to_string(i++));
    }
}

void AlertSystem::stop()
{}

void AlertSystem::onTearDown()
{}

void AlertSystem::setDisabledButtons(bool disable, const ButtonComponent &dontDisable)
{
    for (auto &button: _disabledButtons) {
        auto ptr = static_cast<ButtonComponent *>(button.get());

        if (ptr != &dontDisable)
            ptr->setDisabled(disable);
    }
}