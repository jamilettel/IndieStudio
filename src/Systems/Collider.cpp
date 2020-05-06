/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#include "Systems/Collider.hpp"
#include "Components/Collider.hpp"

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

        ptr->collisions.clear();
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

    return (((position.X < position2.X + collider2->size.X && position.X > position2.X) || 
        (position.X + collider->size.X < position2.X + collider2->size.X && position.X + collider->size.X > position2.X)) &&
        
        ((position.Y < position2.Y + collider2->size.Y && position.Y > position2.Y) || 
        (position.Y + collider->size.Y < position2.Y + collider2->size.Y && position.Y + collider->size.Y > position2.Y)) &&
        
        ((position.Z < position2.Z + collider2->size.Z && position.Z > position2.Z) || 
        (position.Z + collider->size.Z < position2.Z + collider2->size.Z && position.Z + collider->size.Z > position2.Z)));
}