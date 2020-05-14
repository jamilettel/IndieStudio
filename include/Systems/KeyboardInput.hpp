/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardInput
*/

#ifndef KEYBOARDINPUTSYSTEM_HPP_
#define KEYBOARDINPUTSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/KeyboardInput.hpp"
#include "Components/Window.hpp"

namespace is::systems {

    class KeyboardInputSystem: public is::ecs::ASystem {
        public:
            KeyboardInputSystem() = default;
            ~KeyboardInputSystem() override = default;

            KeyboardInputSystem(const KeyboardInputSystem &) = default;
            KeyboardInputSystem &operator=(const KeyboardInputSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::shared_ptr<is::components::WindowComponent> _window;
    };

}

#endif /* !KEYBOARDINPUTSYSTEM_HPP_ */
