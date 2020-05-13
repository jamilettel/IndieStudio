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

namespace is::components {

    class CharacterControllerComponent : public is::ecs::Component {
    public:
        CharacterControllerComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            TransformComponent &transform,
            MovementComponent &movementComponent,
            AudioComponent &audio,
            const std::string &wn = "MainWindow",
            float ps = 0
            );
        ~CharacterControllerComponent() = default;

        CharacterControllerComponent(const CharacterControllerComponent &) = delete;
        CharacterControllerComponent &operator=(const CharacterControllerComponent &) = delete;

        void deleteComponent();

        MovementComponent &getMovementComponent() const noexcept;
        TransformComponent &getTransform() const noexcept;
        AudioComponent &getAudioComponent() const noexcept;

        irr::core::vector3df move;
        float rotateY;

        float playerSpeed;
        std::string windowName;

        bool canPlaceBomb = true;

    private:
        MovementComponent &_movementComponent;
        TransformComponent &_transform;
        AudioComponent &_audioComponent;
    };

}

#endif /* !CharacterController_HPP_ */
