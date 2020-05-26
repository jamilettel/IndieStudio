/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** NetworkInput
*/

#include "Systems/NetworkInput.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void NetworkInputSystem::awake()
{}

void NetworkInputSystem::start()
{
    auto network = _componentManager->getComponentsByType(typeid(NetworkComponent).hash_code());

    if (network.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Network component required for Network Input System");
    _network = std::dynamic_pointer_cast<NetworkComponent>(network[0]);
}

void NetworkInputSystem::stop()
{}

void NetworkInputSystem::onTearDown()
{}

void NetworkInputSystem::update()
{
    std::vector<std::shared_ptr<Component>> &networkComponents =
        _componentManager->getComponentsByType(typeid(NetworkInputComponent).hash_code());

    for (std::shared_ptr<Component> &component: networkComponents) {
        NetworkInputComponent &network = *static_cast<NetworkInputComponent *>(component.get());
    
    }
}
