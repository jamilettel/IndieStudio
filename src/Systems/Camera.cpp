/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCamera
*/

#include "Systems/Camera.hpp"

using namespace irr;

SystemCamera::SystemCamera()
{
}

SystemCamera::~SystemCamera()
{
}

void SystemCamera::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCamera", "Could not get ComponentWindow pointer");
        // apply transfmorm
        ptr->scenemgr->addCameraSceneNode(0, core::vector3df(-20, 20, 0), core::vector3df(1, -1, 0));
    }
}

void SystemCamera::start()
{

}

void SystemCamera::update()
{
    
}

void SystemCamera::stop()
{

}

void SystemCamera::onTearDown()
{

}

