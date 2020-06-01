/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Components/Collider.hpp"
#include "Components/Transform.hpp"

namespace is::components {
    class MovementComponent: public is::ecs::Component {
        public:
            MovementComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                TransformComponent &transform,
                ColliderComponent &collider,
                bool clip = true
                );
            ~MovementComponent() override = default;

            MovementComponent(const MovementComponent &) = delete;
            MovementComponent &operator=(const MovementComponent &) = delete;

            void deleteComponent() override;

            [[nodiscard]] TransformComponent &getTransform() const noexcept;
            [[nodiscard]] ColliderComponent &getCollider() const noexcept;
            [[nodiscard]] bool isOnTheGround() const noexcept;
            void setOnTheGround(bool isOnTheGround) noexcept;

            irr::core::vector3df velocity;
            bool clipping;
            bool sort = true;

        private:
            bool _isOnTheGround = false;
            TransformComponent &_transform;
            ColliderComponent &_collider;
    };

}

#endif /* !MOVEMENT_HPP_ */
