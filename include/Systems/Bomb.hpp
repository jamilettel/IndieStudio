/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemBombSystem_HPP_
#define SystemBombSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

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

            bool dropFire(std::shared_ptr<is::components::BombComponent> ptr,
                         std::shared_ptr<is::components::WindowComponent> ptr_window,
                         int x,
                         int y);

            bool checkFireCollision(is::components::ColliderComponent &trigger,
                                    const std::shared_ptr<is::components::WindowComponent>& ptr_window);
 
            void generateRandomPowerUp(is::components::ColliderComponent *ptr_cc,
                                       std::shared_ptr<is::components::WindowComponent> ptr_window);

        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;
    };

}

#endif /* !SystemBombSystem_HPP_ */
