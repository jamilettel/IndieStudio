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

bool ColliderSystem::checkCollision(ColliderComponent &collider, ColliderComponent &collider2)
{
    collider.position = collider.getTransform().position + collider.offset;
    collider2.position = collider2.getTransform().position + collider2.offset;
    return (((collider.position.X < collider2.position.X + collider2.size.X &&
              collider.position.X >= collider2.position.X) ||
             (collider.position.X + collider.size.X < collider2.position.X + collider2.size.X &&
              collider.position.X + collider.size.X > collider2.position.X)) &&

            ((collider.position.Y < collider2.position.Y + collider2.size.Y &&
              collider.position.Y >= collider2.position.Y) ||
             (collider.position.Y + collider.size.Y < collider2.position.Y + collider2.size.Y &&
              collider.position.Y + collider.size.Y > collider2.position.Y)) &&

            ((collider.position.Z < collider2.position.Z + collider2.size.Z &&
              collider.position.Z >= collider2.position.Z) ||
             (collider.position.Z + collider.size.Z < collider2.position.Z + collider2.size.Z &&
              collider.position.Z + collider.size.Z > collider2.position.Z)));
}
