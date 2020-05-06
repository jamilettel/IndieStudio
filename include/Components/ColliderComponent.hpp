/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider
*/

#ifndef COLLIDERCOMPONENT_HPP_
#define COLLIDERCOMPONENT_HPP_

#include "Components/TransformComponent.hpp"
#include <irrlicht.h>
#include <vector>

namespace is::components {

    class ColliderComponent: public is::ecs::Component {
    public:
        ColliderComponent(std::shared_ptr<is::ecs::Entity> &e, bool check);
        ~ColliderComponent() = default;

        ColliderComponent(const ColliderComponent &) = delete;
        ColliderComponent &operator=(const ColliderComponent &) = delete;

        void checkCollisionWith(std::shared_ptr<is::ecs::Entity> entity);
        std::vector<std::weak_ptr<is::ecs::Entity>> &getEntities();

        irr::core::vector3df offset;
        irr::core::vector3df size;

        bool activeCheck; // ?

        std::vector<std::weak_ptr<is::ecs::Entity>> collisions;

        class ColliderFunctions {
        public:
            ~ColliderFunctions() = delete;

            static bool checkCollision(const ColliderComponent &, const ColliderComponent &);
        };


    private:
        TransformComponent _transform;
    };

}

#endif /* !COLLIDERCOMPONENT_HPP_ */
