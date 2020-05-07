/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#ifndef Fire_HPP_
#define Fire_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"

namespace is::components {

    class FireComponent : public is::ecs::Component {
    public:
        FireComponent(std::shared_ptr<is::ecs::Entity> &e);
        ~FireComponent() = default;

        FireComponent(const FireComponent &) = delete;
        FireComponent &operator=(const FireComponent &) = delete;

        float lifeTime;
    };

}

#endif /* !Fire_HPP_ */
