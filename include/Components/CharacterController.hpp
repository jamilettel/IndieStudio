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

#include "ECS/Component.hpp"

namespace is::components {

    class ComponentCharacterController : public is::ecs::Component {
    public:
        ComponentCharacterController(std::shared_ptr<is::ecs::Entity> &e,
                                     const std::string &wn = "MainWindow",
                                     float ps = 0);
        ~ComponentCharacterController() = default;

        ComponentCharacterController(const ComponentCharacterController &) = delete;
        ComponentCharacterController &operator=(const ComponentCharacterController &) = delete;

        irr::core::vector3df move;
        float rotateY;

        float playerSpeed;
        std::string windowName;
    };

}

#endif /* !CharacterController_HPP_ */
