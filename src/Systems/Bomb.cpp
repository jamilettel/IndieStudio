/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#include "Systems/Bomb.hpp"

#include <utility>

using namespace irr;
using namespace is::components;

void is::systems::BombSystem::awake()
{

}

void is::systems::BombSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Bomb", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void is::systems::BombSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::BombComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::BombComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("BombComponent", "Could not get BombComponent pointer");
        ptr->lifeTime -= _time->get().getCurrentIntervalSeconds();
        if (ptr->lifeTime < 0) {
            std::shared_ptr<is::components::WindowComponent> ptr_window;
            bool windowFound = false;
            for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
                ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
                if (!ptr_window)
                    throw is::exceptions::Exception("BombComponent", "Could not get WindowComponent pointer");
                if (ptr_window->windowName == ptr->getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->windowName) {
                    windowFound = true;
                    break;
                }
            }
            if (!windowFound)
                throw is::exceptions::Exception("BombComponent", "Could not find window");
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, 0, i + 1, ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, i + 1, 0, ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, 0, -(i + 1), ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, -(i + 1), 0, ptr->getCharacterController()); i++);
            dropFire(ptr, ptr_window, 0, 0, ptr->getCharacterController());
            ptr->bomberman->instantBomb--;
            ptr->getEntity()->setDelete(true);
        }
    }
}

bool is::systems::BombSystem::dropFire(std::shared_ptr<is::components::BombComponent> ptr,
                                       std::shared_ptr<is::components::WindowComponent> ptr_window,
                                       int x,
                                       int y,
                                       CharacterControllerComponent &ch)
{
    irr::core::vector3df f = ptr->getEntity()->getComponent<is::components::TransformComponent>()->get()->position;
    f.X = ((int)((f.X + 1.5f) / 3) + x - (f.X < 0)) * 3;
    f.Y = 0;
    f.Z = ((int)((f.Z + 1.5f) / 3) + y - (f.Z < 0)) * 3;
    auto e = this->initRuntimeEntity(is::prefabs::GlobalPrefabs::createFire(f));
    auto part = std::dynamic_pointer_cast<is::components::ParticuleComponent>(*e->getComponent<is::components::ParticuleComponent>());
    part->init(ptr_window);
    auto cc = std::dynamic_pointer_cast<is::components::ColliderComponent>(*e->getComponent<is::components::ColliderComponent>());
    if (checkFireCollision(*cc, ptr_window, ch)) {
        e->setDelete(true);
        return (false);
    }
    return (true);
}


bool is::systems::BombSystem::checkFireCollision(
    is::components::ColliderComponent &trcollider,
    const std::shared_ptr<is::components::WindowComponent>& ptr_window,
    CharacterControllerComponent &ch
)
{
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
    _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (auto & collider : colliders) {
        auto *ptr = static_cast<is::components::ColliderComponent *>(collider.get());

        if (&trcollider == ptr || (!trcollider.collidesWith(ptr->getEntity()->layer) && ptr->getEntity()->layer != is::ecs::Entity::BRKBL_BLK && ptr->getEntity()->layer != is::ecs::Entity::PLAYER))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            if (ptr->getEntity()->layer == is::ecs::Entity::BRKBL_BLK) {
                ptr->getEntity()->setDelete(true);
                auto network = _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code());

                if (network.empty())
                    generateRandomPowerUp(ptr, ptr_window);
                else {
                    auto nw = std::dynamic_pointer_cast<is::components::NetworkComponent>(network[0]);
                    if (nw->playerIdx == 0) {
                        int idx = generateRandomPowerUp(ptr, ptr_window);
                        if (idx) {
                            nw->writeQueue.push("evt pu " + std::to_string(nw->lobby) +
                                                " " + std::to_string(nw->playerIdx) + " " + std::to_string(idx) +
                                                " " + std::to_string(ptr->getTransform().position.X) +
                                                " " + std::to_string(ptr->getTransform().position.Z) + " \n");
                        }
                    }
                }
            }
            if (ptr->getEntity()->layer == is::ecs::Entity::PLAYER) {
                ptr->getEntity()->getComponent<is::components::BombermanComponent>()->get()->dead = true;
                ch.getCharacterComponent().setNbCharactersKilled(ch.getCharacterComponent().getNbCharactersKilled() + 1);
                return (false);
            }
            return (true);
        }
    }
    return (false);
}

int is::systems::BombSystem::generateRandomPowerUp(is::components::ColliderComponent *ptr_cc,
    std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    auto rulesComponents = _componentManager->getComponentsByType(typeid(is::components::RulesComponent).hash_code());
    auto &rules = *std::static_pointer_cast<is::components::RulesComponent>(rulesComponents[0]);

    int i = rand() % 4;
    if (rand() % 4 != 0)
        return (0);
    std::shared_ptr<is::ecs::Entity> e;

    if (i == 0 && rules.useIcon(rules.BOMB))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBombUpPowerUp(ptr_cc->getTransform().position));
    else if (i == 1 && rules.useIcon(rules.ACCELERATOR))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createSpeedUpPowerUp(ptr_cc->getTransform().position));
    else if (i == 2 && rules.useIcon(rules.EXPLOSION))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createFireUpPowerUp(ptr_cc->getTransform().position));
    else if (i == 3 && rules.useIcon(rules.WALL_PASS))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createWallPassPowerUp(ptr_cc->getTransform().position));
    else
        return (0);
    auto ptr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(*e->getComponent<is::components::ModelRendererComponent>());
    ptr->initModelRenderer(std::move(ptr_window));
    return (i + 1);
}

void is::systems::BombSystem::stop()
{

}

void is::systems::BombSystem::onTearDown()
{

}

