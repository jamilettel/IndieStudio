/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#include "Systems/ColliderSystem.hpp"
#include "Components/ColliderComponent.hpp"

using namespace is::system;
using namespace is::components;

void ColliderSystem::awake()
{}

void ColliderSystem::start()
{}

void ColliderSystem::stop()
{}

void ColliderSystem::onTearDown()
{}

void ColliderSystem::update()
{
    std::vector<std::weak_ptr<is::ecs::Component>> &colliders =
        _componentManager->getComponentsByType(typeid(ColliderComponent).hash_code());

    for (size_t i = 0; i < colliders.size(); i++) {
        std::weak_ptr<is::ecs::Component> &elem = colliders[i];
        std::shared_ptr<ColliderComponent> ptr = std::dynamic_pointer_cast<ColliderComponent>(elem.lock());

    }

}
