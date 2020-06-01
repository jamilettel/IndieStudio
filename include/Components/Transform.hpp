/*
** EPITECH PROJECT, 2020
** indie studio
** File description:
** TransformComponent
*/

#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"

namespace is::components {
    class TransformComponent: public is::ecs::Component {
        public:
            explicit TransformComponent(std::shared_ptr<is::ecs::Entity> &e,
                               const irr::core::vector3df& position = irr::core::vector3df(0),
                               const irr::core::vector3df& rotation = irr::core::vector3df(0),
                               const irr::core::vector3df& scale = irr::core::vector3df(1, 1, 1));
            ~TransformComponent() override = default;

            TransformComponent(const TransformComponent &) = delete;
            TransformComponent &operator=(const TransformComponent &) = delete;

            void deleteComponent() override;

            void move(const irr::core::vector3df &vector);
            void rotate(const irr::core::vector3df &vector);
            void scaleObject(const irr::core::vector3df &vector);

            irr::core::vector3df position;
            irr::core::vector3df rotation;
            irr::core::vector3df scale;
    };

}

#endif /* !TRANSFORM_HPP_ */
