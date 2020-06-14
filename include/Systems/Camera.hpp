/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraSystem
*/

#ifndef CAMERASYSTEM_HPP_
#define CAMERASYSTEM_HPP_

#include <memory>
#include <irrlicht.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Camera.hpp"
#include "Components/Window.hpp"
#include "Components/CharacterController.hpp"

namespace is::systems {

    class CameraSystem : public is::ecs::ASystem {
        public:
            CameraSystem() = default;
            ~CameraSystem() override = default;

            CameraSystem(const CameraSystem &) = default;
            CameraSystem &operator=(const CameraSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };

}

#endif /* !CameraSystem_HPP_ */
