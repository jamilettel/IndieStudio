/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider Trigger
*/

#include "Components/ColliderTrigger.hpp"

using namespace is::components;
using namespace is::ecs;

ColliderTriggerComponent::ColliderTriggerComponent(
    std::shared_ptr<Entity> &e,
    ColliderComponent &colliderToCheck,
    std::function<void(std::vector<ColliderComponent *> &)> function
    ):
    Component(e), collider(colliderToCheck), onCollision(std::move(function))
{}

void ColliderTriggerComponent::deleteComponent()
{}
