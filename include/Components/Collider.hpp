/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider
*/

#ifndef COLLIDERCOMPONENT_HPP_
#define COLLIDERCOMPONENT_HPP_

#include "Components/Transform.hpp"
#include <irrlicht.h>
#include <vector>
#include <functional>
#include "ECS/Entity.hpp"

namespace is::components {
    class ColliderComponent: public is::ecs::Component {
        public:
            ColliderComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                TransformComponent &transform,
                const irr::core::vector3df &size = irr::core::vector3df(),
                const irr::core::vector3df &offset = irr::core::vector3df(),
                bool check = true
                );
            ~ColliderComponent() override = default;

            ColliderComponent(const ColliderComponent &) = delete;
            ColliderComponent &operator=(const ColliderComponent &) = delete;

            void deleteComponent() override;

            [[nodiscard]] const TransformComponent &getTransform() const noexcept;

            irr::core::vector3df offset;
            irr::core::vector3df size;

            bool activeCheck;

            std::vector<ColliderComponent *> collisions;

            irr::core::vector3df position;
            irr::core::vector3df center;
            float distance;

            void addCollisionWithLayer(is::ecs::Entity::Layer layer);
            void removeCollisionWithLayer(is::ecs::Entity::Layer layer);
            bool collidesWith(is::ecs::Entity::Layer layer);

        private:
            std::vector<is::ecs::Entity::Layer> _layers;
            TransformComponent &_transform;
    };
}

#endif /* !COLLIDERCOMPONENT_HPP_ */
