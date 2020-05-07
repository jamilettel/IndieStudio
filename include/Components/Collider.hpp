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

namespace is::components {

    class ColliderComponent: public is::ecs::Component {
    public:
        ColliderComponent(std::shared_ptr<is::ecs::Entity> &e,
                          bool check,
                          TransformComponent &transform);
        ~ColliderComponent() = default;

        ColliderComponent(const ColliderComponent &) = delete;
        ColliderComponent &operator=(const ColliderComponent &) = delete;

        std::vector<std::shared_ptr<is::ecs::Entity>> &getEntities();

        irr::core::vector3df offset;
        irr::core::vector3df size;

        bool activeCheck; // ?

        std::vector<std::shared_ptr<is::ecs::Entity>> collisions;

        const TransformComponent &getTransform() const noexcept;

    private:
        TransformComponent &_transform;
    };

}

#endif /* !COLLIDERCOMPONENT_HPP_ */