/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider Trigger
*/

#include "Components/ColliderTrigger.hpp"
#include <utility>

using namespace is::components;

ColliderTriggerComponent::ColliderTriggerComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    ColliderComponent &colliderToCheck,
    std::function<void(std::vector<ColliderComponent *> &)> function
    ):
    Component(e), collider(colliderToCheck), onCollision(std::move(function))
{}

void ColliderTriggerComponent::deleteComponent()
{}
