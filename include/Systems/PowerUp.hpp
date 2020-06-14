/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SYSTEMPOWERUPSYSTEM_HPP_
#define SYSTEMPOWERUPSYSTEM_HPP_

#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <climits>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/PowerUp.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"
#include "Components/Bomberman.hpp"
#include "Systems/Collider.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class PowerUpSystem : public is::ecs::ASystem {
        public:
            PowerUpSystem() = default;
            ~PowerUpSystem() override = default;

            PowerUpSystem(const PowerUpSystem &) = default;
            PowerUpSystem &operator=(const PowerUpSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

            void checkPowerUpCollision(is::components::ColliderComponent &trcollider,
                const std::shared_ptr<is::components::WindowComponent>& ptr_window,
                is::components::PowerUpComponent::PowerUpType type, const is::components::PowerUpComponent &power);
        private:
            std::optional<std::reference_wrapper<is::components::AudioComponent>> _powerupSound; 
    };

}

#endif /* !SystemPowerUpSystem_HPP_ */
