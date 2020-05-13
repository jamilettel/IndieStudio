/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemLightSystem_HPP_
#define SystemLightSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Light.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"

namespace is::systems {

    class LightSystem : public is::ecs::ASystem {
        public:
            LightSystem() = default;
            ~LightSystem() = default;

            LightSystem(const LightSystem &) = default;
            LightSystem &operator=(const LightSystem &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
    };

}

#endif /* !SystemLightSystem_HPP_ */
