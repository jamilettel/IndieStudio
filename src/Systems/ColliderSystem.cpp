/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#include "Systems/ColliderSystem.hpp"
#include "Components/ColliderComponent.hpp"

#include <algorithm>

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
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
        _componentManager->getComponentsByType(typeid(ColliderComponent).hash_code());

    for (size_t i = 0; i < colliders.size(); i++) {
        ColliderComponent *ptr = static_cast<ColliderComponent *>(colliders[i].get());

        if (!ptr->activeCheck)
            continue;
        for (size_t j = 0; j < colliders.size(); j++) {
            if (i == j)
                continue;
            ColliderComponent *collider = static_cast<ColliderComponent *>(colliders[i].get());

            if (checkCollision(ptr, collider))
                ptr->collisions.push_back(collider->getEntity());
        }
    }

}

bool ColliderSystem::checkCollision(ColliderComponent *collider, ColliderComponent *collider2) const
{
    irr::core::vector3df position = collider->getTransform().position + collider->offset;
    irr::core::vector3df position2 = collider2->getTransform().position + collider2->offset;

    if (position.X < position2.X + collider2->size.X && position.X > position2.X)
        return (true);
    return (false);
}