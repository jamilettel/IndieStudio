/*
** EPITECH PROJECT, 2020
** include/Systems/ParticuleSystem.hpp
** File description:
** 
*/

#ifndef PAUSESYSTEM_HPP
#define PAUSESYSTEM_HPP

#include "ECS/ASystem.hpp"
#include "Components/InputManager.hpp"
#include "Exception.hpp"

namespace is::systems {

    class PauseSystem : public is::ecs::ASystem
    {
        public:
            PauseSystem() = default;
            ~PauseSystem() override = default;

            PauseSystem(const PauseSystem &) = default;
            PauseSystem &operator=(const PauseSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::vector<std::shared_ptr<is::ecs::Component>> _inputManagers;
    };
}

#endif
