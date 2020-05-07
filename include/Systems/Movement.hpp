/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Systems/Collider.hpp"
#include "Components/Movement.hpp"

#define SIGN_OF(value) (value < 0 ? -1 : 1)

namespace is::systems {

    class MovementSystem : public is::ecs::ASystem {
    public:
        MovementSystem() = default;
        ~MovementSystem() = default;

        MovementSystem(const MovementSystem &) = default;
        MovementSystem &operator=(const MovementSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    private:
        static void checkCollisions(
            is::components::ColliderComponent &component,
            std::vector<std::shared_ptr<is::ecs::Component>> &colliders
            );
        static void moveOutOfCollision(is::components::MovementComponent &collision);
    };
}

#endif /* !MOVEMENT_HPP_ */
