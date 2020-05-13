/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemFireSystem_HPP_
#define SystemFireSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Fire.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class FireSystem : public is::ecs::ASystem {
        public:
            FireSystem() = default;
            ~FireSystem() = default;

            FireSystem(const FireSystem &) = default;
            FireSystem &operator=(const FireSystem &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

    };

}

#endif /* !SystemFireSystem_HPP_ */
