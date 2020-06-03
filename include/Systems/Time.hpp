/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Time System
*/

#ifndef TIMESYSTEM_HPP_
#define TIMESYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Time.hpp"

namespace is::systems {

    class TimeSystem : public is::ecs::ASystem {
        public:
            TimeSystem() = default;
            ~TimeSystem() override = default;

            TimeSystem(const TimeSystem &) = default;
            TimeSystem &operator=(const TimeSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif //TIMESYSTEM_HPP_
