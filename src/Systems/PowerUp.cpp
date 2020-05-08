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
        if (checkPowerUpCollision(*cc, ptr_window)) {
            ptr->getEntity()->setDelete(true);
        }
    }
}

bool is::systems::PowerUpSystem::checkPowerUpCollision(is::components::ColliderComponent &trcollider, std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
    _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (size_t i = 0; i < colliders.size(); i++) {
        is::components::ColliderComponent *ptr = static_cast<is::components::ColliderComponent *>(colliders[i].get());

        if (&trcollider == ptr || !trcollider.collidesWith(ptr->getEntity()->layer))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            return (true);
        }
    }
    return (false);
}

void is::systems::PowerUpSystem::stop()
{

}

void is::systems::PowerUpSystem::onTearDown()
{

}

