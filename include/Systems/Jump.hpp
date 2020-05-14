/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Jump
*/

#ifndef JUMPSYSTEM_HPP_
#define JUMPSYSTEM_HPP_

#include "ECS/ASystem.hpp"

#include "Components/Jump.hpp"

namespace is::systems {

    class JumpSystem : public is::ecs::ASystem {
        public:
            JumpSystem() = default;
            ~JumpSystem() override = default;

            JumpSystem(const JumpSystem &) = default;
            JumpSystem &operator=(const JumpSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };

}

#endif /* !JUMP_HPP_ */
