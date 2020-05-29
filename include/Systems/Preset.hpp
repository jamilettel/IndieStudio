/*
** EPITECH PROJECT, 2020
** include/Systems/ParticuleSystem.hpp
** File description:
** 
*/

#ifndef PRESETSYSTEM_HPP
#define PRESETSYSTEM_HPP

#include "ECS/ASystem.hpp"
#include "Components/Particule.hpp"
#include "Components/Window.hpp"
#include "Exception.hpp"

namespace is::systems {

    class PresetSystem : public is::ecs::ASystem
    {
        public:
            PresetSystem() = default;
            ~PresetSystem() override = default;

            PresetSystem(const PresetSystem &) = default;
            PresetSystem &operator=(const PresetSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::optional<std::reference_wrapper<is::EventManager>> _eventManager;
            irr::core::array<irr::SJoystickInfo> _joysticks;
            std::shared_ptr<is::components::WindowComponent> _window;
    };
}

#endif
