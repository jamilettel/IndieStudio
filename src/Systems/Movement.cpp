/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#include "Systems/Movement.hpp"
#include "Components/Movement.hpp"
#include <signal.h>
#include <unistd.h>
#include "ECS/Entity.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void MovementSystem::awake()
{}

void MovementSystem::start()
{}

void MovementSystem::stop()
{}

void MovementSystem::onTearDown()
{}

void MovementSystem::checkCollisions(
    ColliderComponent &collider,
    std::vector<std::shared_ptr<Component>> &colliders
    )
{
    for (size_t i = 0; i < colliders.size(); i++) {
        ColliderComponent *ptr = static_cast<ColliderComponent *>(colliders[i].get());

        if (&collider == ptr)
            continue;
        if (ColliderSystem::checkCollision(collider, *ptr)) {
            collider.collisions.emplace_back(ptr);
        }
    }
}

void MovementSystem::moveOutOfCollision(MovementComponent &movement)
{
    ColliderComponent &collider = movement.getCollider();
    irr::core::vector3df position = collider.getTransform().position + collider.offset;

    for (size_t i = 0; i < collider.collisions.size(); i++) {
        ColliderComponent &collider2 = *collider.collisions[i];
        irr::core::vector3df position2 = collider2.getTransform().position + collider2.offset;
        irr::core::vector3df distance;
        irr::core::vector3df absDistance;

        if (position.X > position2.X) {
            distance.X = (position2.X + collider2.size.X) - position.X;
        } else {
            distance.X = (position2.X - collider.size.X) - position.X;
        }
        if (position.Y > position2.Y) {
            distance.Y = (position2.Y + collider2.size.Y) - position.Y;
        } else {
            distance.Y = (position2.Y - collider.size.Y) - position.Y;
        }
        if (position.Z > position2.Z) {
            distance.Z = (position2.Z + collider2.size.Z) - position.Z;
        } else {
            distance.Z = (position2.Z - collider.size.Z) - position.Z;
        }

        absDistance.X = abs(distance.X);
        absDistance.Y = abs(distance.Y);
        absDistance.Z = abs(distance.Z);
        if (absDistance.X < absDistance.Y && absDistance.X < absDistance.Z) {
            movement.getTransform().position.X += distance.X;
            if (SIGN_OF(movement.velocity.X) != SIGN_OF(distance.X))
                movement.velocity.X = 0;
        } else if (absDistance.Y < absDistance.Z) {
            movement.getTransform().position.Y += distance.Y;
            if (SIGN_OF(movement.velocity.Y) != SIGN_OF(distance.Y))
                movement.velocity.Y = 0;
        } else {
            movement.getTransform().position.Z += distance.Z;
            if (SIGN_OF(movement.velocity.Z) != SIGN_OF(distance.Z))
                movement.velocity.Z = 0;
        }
    }
    collider.collisions.clear();
}

void MovementSystem::update()
{
    std::vector<std::shared_ptr<Component>> &movements =
        _componentManager->getComponentsByType(typeid(MovementComponent).hash_code());
    std::vector<std::shared_ptr<Component>> &colliders =
        _componentManager->getComponentsByType(typeid(ColliderComponent).hash_code());
    irr::core::vector3df zero(0, 0, 0);

    for (size_t i = 0; i < movements.size(); i++) {
        MovementComponent *ptr = static_cast<MovementComponent *>(movements[i].get());

        if (ptr->velocity == zero)
            continue;
        ptr->getTransform().position += ptr->velocity;

        if (ptr->clipping) {
            checkCollisions(ptr->getCollider(), colliders);
            moveOutOfCollision(*ptr);
        }
    }
}
