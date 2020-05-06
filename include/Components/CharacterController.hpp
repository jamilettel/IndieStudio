/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#ifndef CharacterController_HPP_
#define CharacterController_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"

class ComponentCharacterController : public is::ecs::Component {
    public:
        ComponentCharacterController(std::shared_ptr<is::ecs::Entity> &e);
        ~ComponentCharacterController() = default;

        ComponentCharacterController(const ComponentCharacterController &) = delete;
        ComponentCharacterController &operator=(const ComponentCharacterController &) = delete;
    protected:
    private:
};

#endif /* !CharacterController_HPP_ */
