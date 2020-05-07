/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Light
*/

#ifndef Light_HPP_
#define Light_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"

namespace is::components {

    class ComponentLight : public is::ecs::Component {
    public:
        ComponentLight(std::shared_ptr<is::ecs::Entity> &e,
                       const std::string &wn,
                       irr::core::vector3df position = irr::core::vector3df(0),
                       irr::video::SColorf color = irr::video::SColorf(0),
                       float radius = 100.0f);
        ~ComponentLight() = default;

        ComponentLight(const ComponentLight &) = delete;
        ComponentLight &operator=(const ComponentLight &) = delete;

        std::string windowName;
        irr::core::vector3df position;
        irr::video::SColorf color;
        float radius;
    };

}

#endif /* !Light_HPP_ */
