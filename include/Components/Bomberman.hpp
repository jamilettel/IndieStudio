/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomberman
*/

#ifndef Bomberman_HPP_
#define Bomberman_HPP_

#include <irrlicht.h>
#include <string>
#include <vector>

#include "ECS/Component.hpp"
#include "Components/PowerUp.hpp"

namespace is::components {

    class BombermanComponent : public is::ecs::Component {
        public:
            explicit BombermanComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~BombermanComponent() override = default;

            BombermanComponent(const BombermanComponent &) = delete;
            BombermanComponent &operator=(const BombermanComponent &) = delete;

            void deleteComponent() override;

            int bombNumber;
            int bombRange;
            float speedMult;
            bool wallPass;

            int instantBomb;
    };

}

#endif /* !Bomberman_HPP_ */
