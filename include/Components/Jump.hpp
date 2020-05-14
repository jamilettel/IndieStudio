/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Jump
*/

#ifndef JUMPCOMPONENT_HPP_
#define JUMPCOMPONENT_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"
#include "Components/Movement.hpp"

namespace is::components {

    class JumpComponent : public is::ecs::Component {
    public:
        JumpComponent(std::shared_ptr<is::ecs::Entity> &e, MovementComponent &movement);
        ~JumpComponent() override = default;

        JumpComponent(const JumpComponent &) = delete;
        JumpComponent &operator=(const JumpComponent &) = delete;

        void deleteComponent() override;
    
        void setJump(bool jump);
        [[nodiscard]] bool isJump() const noexcept;
        [[nodiscard]] MovementComponent &getMovement() const noexcept;
        irr::core::vector3df jumpForce;

    private:
        MovementComponent &_movement;

        bool _jump = false;
    };

}

#endif /* !JUMP_HPP_ */
