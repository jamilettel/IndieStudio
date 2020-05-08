/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#ifndef TIMECOMPONENT_HPP_
#define TIMECOMPONENT_HPP_

#include "ECS/Component.hpp"
#include <irrlicht.h>
#include <chrono>

namespace is::components {

    class TimeComponent : public is::ecs::Component {
        public:
            explicit TimeComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~TimeComponent() override = default;

            TimeComponent(const TimeComponent &) = delete;
            TimeComponent &operator=(const TimeComponent &) = delete;

            void deleteComponent() override;

            void start();

            void setCurrentInterval();
            [[nodiscard]] float getCurrentIntervalSeconds() const;
            [[nodiscard]] float getCurrentIntervalMilliseconds() const;

        private:
            std::chrono::time_point<std::chrono::system_clock> _start;
            std::chrono::time_point<std::chrono::system_clock> _end;
            float _interval_milliseconds;
            float _interval_seconds;

    };
}

#endif //TIMECOMPONENT_HPP_
