/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraSystem
*/

#ifndef CameraSystem_HPP_
#define CameraSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Camera.hpp"
#include "Components/Window.hpp"

namespace is::systems {

    class CameraSystem : public is::ecs::ASystem {
        public:
            CameraSystem() = default;
            ~CameraSystem() = default;

            CameraSystem(const CameraSystem &) = default;
            CameraSystem &operator=(const CameraSystem &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
    };

}

#endif /* !CameraSystem_HPP_ */
