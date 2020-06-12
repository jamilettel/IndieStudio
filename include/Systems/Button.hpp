/*
** EPITECH PROJECT, 2020
** include/Systems/ButtonSystem.hpp
** File description:
** 
*/

#ifndef BUTTONSYSTEM_HPP
#define BUTTONSYSTEM_HPP

#include "ECS/ASystem.hpp"

#include "Components/Button.hpp"
#include "Exception.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class ButtonSystem: public is::ecs::ASystem {
        public:
            ButtonSystem() = default;
            ~ButtonSystem() override = default;

            ButtonSystem(const ButtonSystem &) = default;
            ButtonSystem &operator=(const ButtonSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::optional<std::reference_wrapper<is::components::AudioComponent>> _clickSound;
    };
}

#endif
