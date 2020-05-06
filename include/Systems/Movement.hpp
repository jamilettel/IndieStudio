/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#ifndef MOVEMENTSYSTEM_HPP_
#define MOVEMENTSYSTEM_HPP_

#include "ECS/ASystem.hpp"

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
    };
}

#endif /* !MOVEMENT_HPP_ */
