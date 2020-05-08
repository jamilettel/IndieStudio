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

namespace is::components {

    class JumpComponent : public is::ecs::Component {
    public:
        JumpComponent(std::shared_ptr<is::ecs::Entity> &e);
        ~JumpComponent() = default;

        JumpComponent(const JumpComponent &) = delete;
        JumpComponent &operator=(const JumpComponent &) = delete;
    };

}

#endif /* !JUMP_HPP_ */
