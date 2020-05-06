/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#ifndef Camera_HPP_
#define Camera_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"

class ComponentCamera : public is::ecs::Component {
    public:
        ComponentCamera(std::shared_ptr<is::ecs::Entity> &e);
        ~ComponentCamera() = default;

        ComponentCamera(const ComponentCamera &) = delete;
        ComponentCamera &operator=(const ComponentCamera &) = delete;
    protected:
    private:
};

#endif /* !Camera_HPP_ */
