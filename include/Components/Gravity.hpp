/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gravity
*/

#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include "ECS/Component.hpp"

class ComponentGravity : public is::ecs::Component {
    public:
        ComponentGravity(std::shared_ptr<is::ecs::Entity> &e);
        ~ComponentGravity() = default;

    protected:
    private:
};

#endif /* !GRAVITY_HPP_ */
