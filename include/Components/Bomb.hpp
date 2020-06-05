/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Components/Bomberman.hpp"
#include "Components/CharacterController.hpp"

namespace is::components {

    class BombComponent : public is::ecs::Component {
        public:
            BombComponent(std::shared_ptr<is::ecs::Entity> &e,
                std::shared_ptr<is::components::BombermanComponent> &bm,
                const irr::core::vector3df &pos,
                CharacterControllerComponent &character,
                float lt = 3,
                int size = 2
            );
            ~BombComponent() override = default;

            BombComponent(const BombComponent &) = delete;
            BombComponent &operator=(const BombComponent &) = delete;

            void deleteComponent() override;

            float lifeTime;
            float bombSize;
            std::shared_ptr<is::components::BombermanComponent> bomberman;
            irr::core::vector3df _pos;

            CharacterControllerComponent &getCharacterController() const noexcept;

        private:
            CharacterControllerComponent &_character;
    };

}

#endif /* !BOMB_HPP_ */
