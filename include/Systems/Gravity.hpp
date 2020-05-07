/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Gravity
*/

#ifndef GRAVITYSYSTEM_HPP_
#define GRAVITYSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Collider.hpp"
#include "Components/Gravity.hpp"
#include "ECS/Component.hpp"

namespace is::systems {

    class GravitySystem: public is::ecs::ASystem {
    public:
        GravitySystem() = default;
        ~GravitySystem() = default;

        GravitySystem(const GravitySystem &) = default;
        GravitySystem &operator=(const GravitySystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;
    };

}

#endif /* !GRAVITY_HPP_ */
