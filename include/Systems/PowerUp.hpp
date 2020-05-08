/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemPowerUpSystem_HPP_
#define SystemPowerUpSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/PowerUp.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"
#include "Systems/Collider.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class PowerUpSystem : public is::ecs::ASystem {
        public:
            PowerUpSystem() = default;
            ~PowerUpSystem() = default;

            PowerUpSystem(const PowerUpSystem &) = default;
            PowerUpSystem &operator=(const PowerUpSystem &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

            bool checkPowerUpCollision(is::components::ColliderComponent &trcollider, std::shared_ptr<is::components::WindowComponent> ptr_window);


        protected:
        private:

    };

}

#endif /* !SystemPowerUpSystem_HPP_ */
