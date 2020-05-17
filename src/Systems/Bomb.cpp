/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#include "Systems/Bomb.hpp"

#include <utility>

using namespace irr;

void is::systems::BombSystem::awake()
{

}

void is::systems::BombSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Bomb", "No time component in scene");
    _time.emplace(*dynamic_cast<is::components::TimeComponent *>(time[0].get()));
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
                throw is::exceptions::Exception("BombComponent", "Could not found window");
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, 0, i + 1); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, i + 1, 0); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, 0, -(i + 1)); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, ptr_window, -(i + 1), 0); i++);
            dropFire(ptr, ptr_window, 0, 0);
            ptr->bomberman->instantBomb--;
            ptr->getEntity()->setDelete(true);
        }
    }
}

bool is::systems::BombSystem::dropFire(std::shared_ptr<is::components::BombComponent> ptr,
                                       std::shared_ptr<is::components::WindowComponent> ptr_window,
                                       int x,
                                       int y)
{
    irr::core::vector3df f = ptr->getEntity()->getComponent<is::components::TransformComponent>()->get()->position;
    f.X = ((int)((f.X + 1.5f) / 3) + x - (f.X < 0)) * 3;
    f.Y = 0;
    f.Z = ((int)((f.Z + 1.5f) / 3) + y - (f.Z < 0)) * 3;
    auto e = this->initRuntimeEntity(is::prefabs::GlobalPrefabs::createFire(f));
    auto mr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(*e->getComponent<is::components::ModelRendererComponent>());
    mr->initModelRenderer(ptr_window);
    auto cc = std::dynamic_pointer_cast<is::components::ColliderComponent>(*e->getComponent<is::components::ColliderComponent>());
    if (checkFireCollision(*cc, ptr_window)) {
        e->setDelete(true);
        return (false);
    }
    return (true);
}


bool is::systems::BombSystem::checkFireCollision(is::components::ColliderComponent &trcollider, const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
    _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (auto & collider : colliders) {
        auto *ptr = dynamic_cast<is::components::ColliderComponent *>(collider.get());

        if (&trcollider == ptr || (!trcollider.collidesWith(ptr->getEntity()->layer) && ptr->getEntity()->layer != is::ecs::Entity::BRKBL_BLK && ptr->getEntity()->layer != is::ecs::Entity::PLAYER))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            if (ptr->getEntity()->layer == is::ecs::Entity::BRKBL_BLK) {
                ptr->getEntity()->setDelete(true);
                generateRandomPowerUp(ptr, ptr_window);
            }
            if (ptr->getEntity()->layer == is::ecs::Entity::PLAYER) {
                ptr->getEntity()->setDelete(true);
                return (false);
            }
            return (true);
        }
    }
    return (false);
}

void is::systems::BombSystem::generateRandomPowerUp(is::components::ColliderComponent *ptr_cc,
    std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    int i = rand() % 4;
    if (rand() % 4 != 0)
        return;
    std::shared_ptr<is::ecs::Entity> e;
    if (i == 0)
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBombUpPowerUp(ptr_cc->getTransform().position));
    else if (i == 1)
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createSpeedUpPowerUp(ptr_cc->getTransform().position));
    else if (i == 2)
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createFireUpPowerUp(ptr_cc->getTransform().position));
     else if (i == 3)
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createWallPassPowerUp(ptr_cc->getTransform().position));
    auto ptr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(*e->getComponent<is::components::ModelRendererComponent>());
    ptr->initModelRenderer(std::move(ptr_window));
}

void is::systems::BombSystem::stop()
{

}

void is::systems::BombSystem::onTearDown()
{

}

