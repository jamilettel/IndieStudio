/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#ifndef CharacterController_HPP_
#define CharacterController_HPP_

#include <irrlicht.h>
#include <string>

#include "Components/Movement.hpp"
#include "Components/Audio.hpp"
#include "Components/Character.hpp"

namespace is::components {

    class CharacterControllerComponent : public is::ecs::Component {
        public:
            CharacterControllerComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                TransformComponent &transform,
                MovementComponent &movementComponent,
                AudioComponent &audio,
                CharacterComponent &character,
                std::string wn = "MainWindow",
                float ps = 0
            );
            ~CharacterControllerComponent() override = default;

            CharacterControllerComponent(const CharacterControllerComponent &) = delete;
            CharacterControllerComponent &operator=(const CharacterControllerComponent &) = delete;

            void deleteComponent() override;

            [[nodiscard]] MovementComponent &getMovementComponent() const noexcept;
            [[nodiscard]] TransformComponent &getTransform() const noexcept;
            [[nodiscard]] AudioComponent &getAudioComponent() const noexcept;
            [[nodiscard]] CharacterComponent &getCharacterComponent() const noexcept;

            irr::core::vector3df move;
            float rotateY;

            float playerSpeed;
            std::string windowName;

            bool canPlaceBomb = true;

            bool operator==(const CharacterControllerComponent &character) const noexcept;

        private:
            MovementComponent &_movementComponent;
            TransformComponent &_transform;
            AudioComponent &_audioComponent;
            CharacterComponent &_character;
            int _id;
    };

}

#endif /* !CharacterController_HPP_ */
