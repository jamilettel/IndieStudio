/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickInput
*/

#ifndef JOYSTICKINPUTSYSTEM_HPP_
#define JOYSTICKINPUTSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/JoystickInput.hpp"
#include "Components/Window.hpp"

namespace is::systems {

    class JoystickInputSystem: public is::ecs::ASystem {
        public:
            JoystickInputSystem() = default;
            ~JoystickInputSystem() override = default;

            JoystickInputSystem(const JoystickInputSystem &) = default;
            JoystickInputSystem &operator=(const JoystickInputSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::optional<std::reference_wrapper<irr::core::array<irr::SJoystickInfo>>> _joysticks;
            std::optional<std::reference_wrapper<is::EventManager>> _eventManager;
    };

}

#endif /* !JOYSTICKINPUTSYSTEM_HPP_ */
