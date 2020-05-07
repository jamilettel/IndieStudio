/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCharacterController
*/

#ifndef SystemCharacterController_HPP_
#define SystemCharacterController_HPP_

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

    class SystemCharacterController : public is::ecs::ASystem {
    public:
        SystemCharacterController() = default;
        ~SystemCharacterController() = default;

        SystemCharacterController(const SystemCharacterController &) = default;
        SystemCharacterController &operator=(const SystemCharacterController &) = default;

        void awake();
        void start();
        void update();
        void stop();
        void onTearDown();
    
        void rotateToDirection(irr::core::vector3df move, irr::core::vector3df &rotate);
        void rotateToAngle(irr::core::vector3df &rotate, float angle);

    protected:
    private:
    };

}

#endif /* !SystemCharacterController_HPP_ */
