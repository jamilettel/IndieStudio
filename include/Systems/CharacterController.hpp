/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterControllerSystem
*/

#ifndef CharacterControllerSystem_HPP_
#define CharacterControllerSystem_HPP_
#define _USE_MATH_DEFINES

#define _USE_MATH_DEFINES

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <cmath>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/CharacterController.hpp"
#include "Components/Transform.hpp"
#include "Components/Movement.hpp"
#include "Components/Window.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class CharacterControllerSystem : public is::ecs::ASystem {
        public:
            CharacterControllerSystem() = default;
            ~CharacterControllerSystem() override = default;

            CharacterControllerSystem(const CharacterControllerSystem &) = default;
            CharacterControllerSystem &operator=(const CharacterControllerSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

            void rotateToDirection(irr::core::vector3df move, irr::core::vector3df &rotate);
            void rotateToAngle(irr::core::vector3df &rotate, float angle);

        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

    };

}

#endif /* !CharacterControllerSystem_HPP_ */
