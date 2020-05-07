/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#include "Components/Camera.hpp"

is::components::ComponentCamera::ComponentCamera(std::shared_ptr<is::ecs::Entity> &e,
                                                 const std::string &cm,
                                                 const std::string &wm,
                                                 irr::core::vector3df pos,
                                                 irr::core::vector3df rot) :
Component(e)
{
    position = pos;
    rotation = rot;
    cameraName = cm;
    windowName = wm;
}
