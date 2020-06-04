/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "ECS/ASystem.hpp"

#include "Components/Timer.hpp"

namespace is::systems
{
    class TimerSystem : public is::ecs::ASystem {
        public:
            TimerSystem() = default;
            ~TimerSystem() override = default;

            TimerSystem(const TimerSystem &) = default;
            TimerSystem &operator=(const TimerSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}


#endif /* !TIMER_HPP_ */
