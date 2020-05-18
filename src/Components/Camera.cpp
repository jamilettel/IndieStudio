/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#include "Components/Camera.hpp"

is::components::CameraComponent::CameraComponent(std::shared_ptr<is::ecs::Entity> &e,
                                                 const std::string &cm,
                                                 const std::string &wm,
                                                 const irr::core::vector3df& pos,
                                                 const irr::core::vector3df& rot,
                                                 bool gm) :
Component(e)
{
    position = pos;
    rotation = rot;
    cameraName = cm;
    windowName = wm;

    gameCamera = gm;
}

void is::components::CameraComponent::deleteComponent()
{
    
}
