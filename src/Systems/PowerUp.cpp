/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUpSystem
*/

#include "Systems/PowerUp.hpp"

using namespace irr;

void is::systems::PowerUpSystem::awake()
{

}

void is::systems::PowerUpSystem::start()
{

}

void is::systems::PowerUpSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::PowerUpComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::PowerUpComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("BombComponent", "Could not get BombComponent pointer");
        
        std::shared_ptr<is::components::WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("CharacterControllerSystem", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found window");
        auto cc = std::dynamic_pointer_cast<is::components::ColliderComponent>(*ptr->getEntity()->getComponent<is::components::ColliderComponent>());
        checkPowerUpCollision(*cc, ptr_window, ptr->type);
    }
}

void is::systems::PowerUpSystem::checkPowerUpCollision(is::components::ColliderComponent &trcollider,
    const std::shared_ptr<is::components::WindowComponent>& ptr_window,
    is::components::PowerUpComponent::PowerUpType type)
{
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
    _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (auto & collider : colliders) {
        auto *ptr = static_cast<is::components::ColliderComponent *>(collider.get());

        if (&trcollider == ptr || !trcollider.collidesWith(ptr->getEntity()->layer))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            auto bm = ptr->getEntity()->getComponent<is::components::BombermanComponent>();
            if (!bm)
                throw is::exceptions::Exception("PowerUpSystem", "Could not found bomberman");
            switch (type) {
            case is::components::PowerUpComponent::BOMB_UP:
                bm->get()->bombNumber++;
                break;
            case is::components::PowerUpComponent::SPEED_UP:
                bm->get()->speedMult++;
                break;
            case is::components::PowerUpComponent::FIRE_UP:
                bm->get()->bombRange++;
                break;
            case is::components::PowerUpComponent::WALL_PASS:
                ptr->getEntity()->getComponent<is::components::ColliderComponent>()->get()->removeCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
                break;
            }
            trcollider.getEntity()->setDelete(true);
            return;
        }
    }
}

void is::systems::PowerUpSystem::stop()
{

}

void is::systems::PowerUpSystem::onTearDown()
{

}

