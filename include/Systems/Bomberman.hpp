/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemBombermanSystem_HPP_
#define SystemBombermanSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Bomberman.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class BombermanSystem : public is::ecs::ASystem {
        public:
            BombermanSystem() = default;
            ~BombermanSystem() = default;

            BombermanSystem(const BombermanSystem &) = default;
            BombermanSystem &operator=(const BombermanSystem &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
    };

}

#endif /* !SystemBombermanSystem_HPP_ */
