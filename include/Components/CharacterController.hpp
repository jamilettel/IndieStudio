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

    class ComponentCharacterController : public is::ecs::Component {
    public:
        ComponentCharacterController(
            std::shared_ptr<is::ecs::Entity> &e,
            TransformComponent &transform,
            MovementComponent &movementComponent,
            ComponentAudio &audio,
            const std::string &wn = "MainWindow",
            float ps = 0,
            float playerJumpSeed = 0
            );
        ~ComponentCharacterController() = default;

        ComponentCharacterController(const ComponentCharacterController &) = delete;
        ComponentCharacterController &operator=(const ComponentCharacterController &) = delete;

        MovementComponent &getMovementComponent() const noexcept;
        TransformComponent &getTransform() const noexcept;
        ComponentAudio &getAudioComponent() const noexcept;

        irr::core::vector3df move;
        float rotateY;

        float playerSpeed;
        std::string windowName;

        bool jump;
        float jumpSpeed;

    private:
        MovementComponent &_movementComponent;
        TransformComponent &_transform;
        ComponentAudio &_audioComponent;
    };

}

#endif /* !CharacterController_HPP_ */
