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
#include "Components/Bomberman.hpp"

namespace is::components {

    class BombComponent : public is::ecs::Component {
    public:
        BombComponent(std::shared_ptr<is::ecs::Entity> &e,
            std::shared_ptr<is::components::BombermanComponent> &bm,
            float lt = 3,
            int size = 2);
        ~BombComponent() override = default;

        BombComponent(const BombComponent &) = delete;
        BombComponent &operator=(const BombComponent &) = delete;

        void deleteComponent() override;

        float lifeTime;
        float bombSize;
        std::shared_ptr<is::components::BombermanComponent> bomberman;

    };

}

#endif /* !Bomb_HPP_ */
