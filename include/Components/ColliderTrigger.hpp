/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider Trigger
*/

#ifndef COLLIDERTRIGGERCOMPONENT_HPP_
#define COLLIDERTRIGGERCOMPONENT_HPP_

#include "Components/Collider.hpp"

namespace is::components {

    class ColliderTriggerComponent: public is::ecs::Component {
    public:
        ColliderTriggerComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            ColliderComponent &colliderToCheck,
            std::function<void(std::vector<ColliderComponent *> &)> onCollisionFct
            );
        ~ColliderTriggerComponent() override = default;

        ColliderTriggerComponent(const ColliderTriggerComponent &) = delete;
        ColliderTriggerComponent &operator=(const ColliderTriggerComponent &) = delete;

        void deleteComponent() override;

        ColliderComponent &collider;
        std::function<void(std::vector<ColliderComponent *> &)> onCollision;
        bool check = true;

    };

}

#endif /* !COLLIDERTRIGGERCOMPONENT_HPP_ */
