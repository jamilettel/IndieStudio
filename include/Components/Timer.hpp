/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Timer
*/

#ifndef TIMERCOMPONENT_HPP_
#define TIMERCOMPONENT_HPP_

#include "ECS/Component.hpp"

#include "Components/Text.hpp"
#include "Components/Time.hpp"

namespace is::components
{
    class TimerComponent : public is::ecs::Component {
        public:
            TimerComponent(std::shared_ptr<is::ecs::Entity> &e, TextComponent &text, TimeComponent &timeComponent, float time);
            ~TimerComponent() override = default;

            TimerComponent(const TimerComponent &) = delete;
            TimerComponent &operator=(const TimerComponent &) = delete;

            void deleteComponent() override;

            void update();

        private:
            float _time; // * in seconds
            TextComponent &_text;
            TimeComponent &_timeC;
    };
}


#endif /* !TIMER_HPP_ */
