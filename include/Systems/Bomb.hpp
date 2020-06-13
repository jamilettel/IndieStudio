/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SYSTEMBOMBSYSTEM_HPP_
#define SYSTEMBOMBSYSTEM_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <climits>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "ECS/Entity.hpp"
#include "Game.hpp"

#include "Components/Bomb.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"
#include "Components/ColliderTrigger.hpp"
#include "Components/Collider.hpp"
#include "Components/Time.hpp"
#include "Components/Network.hpp"
#include "Components/Rules.hpp"
#include "Components/CharacterController.hpp"

#include "Systems/Collider.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class BombSystem : public is::ecs::ASystem {
        public:
            BombSystem() = default;
            ~BombSystem() override = default;

            BombSystem(const BombSystem &) = default;
            BombSystem &operator=(const BombSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

            bool dropFire(
                const std::shared_ptr<is::components::BombComponent>& ptr,
                const std::shared_ptr<is::components::WindowComponent>& ptr_window,
                int x,
                int y,
                is::components::CharacterControllerComponent &character
            );

            bool checkFireCollision(
                is::components::ColliderComponent &trigger,
                const std::shared_ptr<is::components::WindowComponent>& ptr_window,
                is::components::CharacterControllerComponent &ch
            );
 
            int generateRandomPowerUp(is::components::ColliderComponent *ptr_cc,
                                       const std::shared_ptr<is::components::WindowComponent>& ptr_window);

        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;
            std::optional<std::reference_wrapper<is::components::AudioComponent>> _deathSound;
    };

}

#endif /* !SYSTEMBOMBSYSTEM_HPP_ */
