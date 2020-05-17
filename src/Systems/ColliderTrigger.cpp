/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider Trigger
*/

#include "Systems/ColliderTrigger.hpp"
#include "Components/ColliderTrigger.hpp"
#include <algorithm>

using namespace is::components;
using namespace is::systems;
using namespace is::ecs;

void ColliderTriggerSystem::awake()
{}

void ColliderTriggerSystem::start()
{}

void ColliderTriggerSystem::stop()
{}

void ColliderTriggerSystem::onTearDown()
{}

void ColliderTriggerSystem::update()
{
    std::vector<std::shared_ptr<Component>> &triggers =
        _componentManager->getComponentsByType(typeid(ColliderTriggerComponent).hash_code());
    std::vector<std::shared_ptr<Component>> &colliders =
        _componentManager->getComponentsByType(typeid(ColliderComponent).hash_code());

    for (std::shared_ptr<Component> &elem: triggers) {
        auto *trigger = static_cast<ColliderTriggerComponent *>(elem.get());

        if (!trigger->check)
            continue;

        ColliderSystem::precomputeCollisionVariables(trigger->collider);
        for (auto & collider : colliders) {
            auto *ptr = static_cast<ColliderComponent *>(collider.get());

            if (&trigger->collider == ptr || !trigger->collider.collidesWith(ptr->getEntity()->layer))
                continue;
            ColliderSystem::precomputeCollisionVariables(*ptr);
            if (ColliderSystem::checkCollision(trigger->collider, *ptr)) {
                trigger->collider.collisions.emplace_back(ptr);
            }
        }
        if (!trigger->collider.collisions.empty()) {
            trigger->onCollision(trigger->collider.collisions);
            trigger->collider.collisions.clear();
        }
    }
}
