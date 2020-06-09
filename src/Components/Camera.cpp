/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#include "Components/Camera.hpp"

#include <utility>

using namespace is::components;
using namespace is::ecs;

CameraComponent::CameraComponent(std::shared_ptr<Entity> &e,
                                 std::string cm,
                                 std::string wm,
                                 const irr::core::vector3df& pos,
                                 const irr::core::vector3df& rot,
                                 bool gm) :
Component(e), position(pos), rotation(rot), cameraName(std::move(cm)), windowName(std::move(wm)), gameCamera(gm)
{
}

void CameraComponent::deleteComponent()
{
    
}
