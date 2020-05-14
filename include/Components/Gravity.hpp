/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Gravity
*/

#ifndef GRAVITYCOMPONENT_HPP_
#define GRAVITYCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Components/Movement.hpp"

#include <irrlicht.h>
#include <vector>

namespace is::components {

    class GravityComponent: public is::ecs::Component {
    public:
        GravityComponent(std::shared_ptr<is::ecs::Entity> &e, MovementComponent &movement);
        ~GravityComponent() override = default;

        GravityComponent(const GravityComponent &) = delete;
        GravityComponent &operator=(const GravityComponent &) = delete;

        void deleteComponent() override;

        void setActive(bool use);
        [[nodiscard]] bool isActive() const noexcept;
        [[nodiscard]] MovementComponent &getMovement() const noexcept;

        irr::core::vector3df gravity;

    private:
        bool _active = true;
        MovementComponent &_movement;
    };
}

#endif /* !GRAVITY_HPP_ */
