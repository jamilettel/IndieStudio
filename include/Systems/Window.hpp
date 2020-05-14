/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowSystem
*/

#ifndef WindowSystem_HPP_
#define WindowSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Time.hpp"
#include "Components/Window.hpp"
#include "Game.hpp"

namespace is::systems {

    class WindowSystem : public is::ecs::ASystem {
        public:
            WindowSystem() = default;
            ~WindowSystem() override = default;

            WindowSystem(const WindowSystem &) = default;
            WindowSystem &operator=(const WindowSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

            void manageJoysticks(std::shared_ptr<is::components::WindowComponent> &ptr);

        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;
    };

}

#endif /* !WindowSystem_HPP_ */
