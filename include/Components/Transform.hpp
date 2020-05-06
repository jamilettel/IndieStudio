/*
** EPITECH PROJECT, 2020
** indie studio
** File description:
** window
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "ECS/Component.hpp"
#include <irrlicht.h>

namespace is::components {

    class TransformComponent: public is::ecs::Component {
    public:
        TransformComponent(std::shared_ptr<is::ecs::Entity> &e,
            irr::core::vector3df position = irr::core::vector3df(0),
            irr::core::vector3df rotation = irr::core::vector3df(0),
            irr::core::vector3df scale = irr::core::vector3df(1, 1, 1));
        ~TransformComponent() = default;

        TransformComponent(const TransformComponent &) = delete;
        TransformComponent &operator=(const TransformComponent &) = delete;

        void move(const irr::core::vector3df &vector);
        void rotate(const irr::core::vector3df &vector);
        void scaleObject(const irr::core::vector3df &vector);

        irr::core::vector3df position;
        irr::core::vector3df rotation;
        irr::core::vector3df scale;

    };

}

#endif /* !TRANSFORM_HPP_ */
