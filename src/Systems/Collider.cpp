/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#include "Systems/Collider.hpp"
#include "Components/Collider.hpp"

#include <algorithm>

using namespace is::systems;
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
}

void ColliderSystem::precomputeCollisionVariables(ColliderComponent &collider)
{
    collider.position = collider.getTransform().position + collider.offset;
    collider.center = collider.position + collider.size/2;
}


bool ColliderSystem::checkCollision(ColliderComponent &collider, ColliderComponent &collider2)
{
    return ((abs(collider.center.X - collider2.center.X) < (collider.size.X + collider2.size.X)/2.0) &&
            (abs(collider.center.Y - collider2.center.Y) < (collider.size.Y + collider2.size.Y)/2.0) &&
            (abs(collider.center.Z - collider2.center.Z) < (collider.size.Z + collider2.size.Z)/2.0));
}
