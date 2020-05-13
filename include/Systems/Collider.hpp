/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#ifndef COLLIDERSYSTEM_HPP_
#define COLLIDERSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Collider.hpp"

namespace is::systems {

    class ColliderSystem: public is::ecs::ASystem {
    public:
        ColliderSystem() = delete;
        ~ColliderSystem() = default;

        ColliderSystem(const ColliderSystem &) = default;
        ColliderSystem &operator=(const ColliderSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

        static void precomputeCollisionVariables(
            is::components::ColliderComponent &
            );
        static bool checkCollision(
            is::components::ColliderComponent &collider,
            is::components::ColliderComponent &collider2
            );
    };

}

#endif /* !COLLIDERSYSTEM_HPP_ */
