/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUp
*/

#ifndef PowerUp_HPP_
#define PowerUp_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"

namespace is::components {

    class PowerUpComponent : public is::ecs::Component {
    public:
        enum PowerUpType {
            BOMB_UP,
            SPEED_UP,
            FIRE_UP,
            WALL_PASS
        };

        PowerUpComponent(std::shared_ptr<is::ecs::Entity> &e, PowerUpType tp);
        ~PowerUpComponent() override = default;

        PowerUpComponent(const PowerUpComponent &) = delete;
        PowerUpComponent &operator=(const PowerUpComponent &) = delete;

        void deleteComponent() override;

        PowerUpType type;
    };

}

#endif /* !PowerUp_HPP_ */
