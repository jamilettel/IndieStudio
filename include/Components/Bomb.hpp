/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef Bomb_HPP_
#define Bomb_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"

namespace is::components {

    class BombComponent : public is::ecs::Component {
    public:
        BombComponent(std::shared_ptr<is::ecs::Entity> &e);
        ~BombComponent() = default;

        BombComponent(const BombComponent &) = delete;
        BombComponent &operator=(const BombComponent &) = delete;

        void deleteComponent();

        float lifeTime;

    };

}

#endif /* !Bomb_HPP_ */
