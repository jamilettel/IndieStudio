/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Components/Transform.hpp"

#include <irrlicht.h>

namespace is::components {

    class MovementComponent: public is::ecs::Component {
    public:
        MovementComponent(std::shared_ptr<is::ecs::Entity> &e, TransformComponent &transform, bool clip = false);
        ~MovementComponent() = default;

        MovementComponent(const MovementComponent &) = delete;
        MovementComponent &operator=(const MovementComponent &) = delete;

        TransformComponent &getTransform() const noexcept;

        irr::core::vector3df velocity;
        bool clipping;

        private:
        TransformComponent &_transform;
    };

}

#endif /* !MOVEMENT_HPP_ */
