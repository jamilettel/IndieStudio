/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** NetworkInput
*/

#include "Systems/NetworkInput.hpp"
#include "Prefabs/GlobalPrefabs.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void NetworkInputSystem::awake()
{
    std::vector<std::shared_ptr<Component>> &mulComponents =
        _componentManager->getComponentsByType(typeid(NetworkInputComponent).hash_code());
    for (std::shared_ptr<Component> &component: mulComponents) {
        if (component->getEntity()->isInit())
            continue;
        NetworkInputComponent &mul = *static_cast<NetworkInputComponent *>(component.get());
        mul.getInputManager().addValue("MoveHorizontalAxis", 0);
        mul.getInputManager().addValue("MoveVerticalAxis", 0);
        mul.getInputManager().addValue("Jump", 0);
        mul.getInputManager().addValue("DropBomb", 0);
    }
}

void NetworkInputSystem::start()
{
    auto network = _componentManager->getComponentsByType(typeid(NetworkComponent).hash_code());

    if (network.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Network component required for Network Input System");
    _network = std::static_pointer_cast<NetworkComponent>(network[0]);
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
        int idx = network.id;
        auto tr = network.getEntity()->getComponent<TransformComponent>()->get();
        tr->position = {
            _network->playerStates[idx].position.X,
            0,
            _network->playerStates[idx].position.Y
        };
        tr->rotation.Y = _network->playerStates[idx].rotationY;
        network.getInputManager().setValue("DropBomb", 0);
        if (_network->playerStates[idx].dropBomb) {
            network.getInputManager().setValue("DropBomb", 1);
            _network->playerStates[idx].dropBomb = false;
        }
        if (_network->playerStates[idx].powerUpSpawn) {
            std::shared_ptr<is::ecs::Entity> e;
            int i = _network->playerStates[idx].powerUpSpawn - 1;
            std::vector<std::shared_ptr<is::ecs::Component>> &window =
                _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
            if (!window.size())
                throw is::exceptions::Exception("NetworkInput", "No window component in scene");
            const auto &ptr_window = std::static_pointer_cast<is::components::WindowComponent>(window[0]);

            if (i == 0)
                e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBombUpPowerUp({_network->playerStates[idx].positionPowerUp.X, 0, _network->playerStates[idx].positionPowerUp.Y}));
            else if (i == 1)
                e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createSpeedUpPowerUp({_network->playerStates[idx].positionPowerUp.X, 0, _network->playerStates[idx].positionPowerUp.Y}));
            else if (i == 2)
                e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createFireUpPowerUp({_network->playerStates[idx].positionPowerUp.X, 0, _network->playerStates[idx].positionPowerUp.Y}));
            else if (i == 3)
                e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createWallPassPowerUp({_network->playerStates[idx].positionPowerUp.X, 0, _network->playerStates[idx].positionPowerUp.Y}));
            const auto &ptr = static_cast<is::components::ModelRendererComponent*>(e->getComponent<is::components::ModelRendererComponent>()->get());
            ptr->initModelRenderer(std::move(ptr_window));
            _network->playerStates[idx].powerUpSpawn = 0;
        }
        if (_network->playerStates[idx].powerUpTake) {
            int i = _network->playerStates[idx].powerUpTake - 1;
            const auto &bm = network.getEntity()->getComponent<BombermanComponent>()->get();
            if (!bm)
                throw is::exceptions::Exception("NetworkInputSystem", "Could not find bomberman");
            switch (i) {
            case is::components::PowerUpComponent::BOMB_UP:
                bm->bombNumber++;
                break;
            case is::components::PowerUpComponent::SPEED_UP:
                bm->speedMult++;
                bm->speedCount++;
                break;
            case is::components::PowerUpComponent::FIRE_UP:
                bm->bombRange++;
                break;
            }
            _network->playerStates[idx].powerUpTake = 0;
        }
    }
}
