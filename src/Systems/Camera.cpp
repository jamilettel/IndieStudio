/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraSystem
*/

#include "Systems/Camera.hpp"

using namespace irr;

void is::systems::CameraSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::CameraComponent>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("CameraSystem", "Could not get CameraComponent pointer");
        for (auto &cw : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            auto ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(cw);
            if (!ptr_window)
                throw new is::exceptions::Exception("CameraSystem", "Could not get WindowComponent pointer");
            if (ptr->windowName != ptr_window->windowName)
                continue;
            ptr_window->scenemgr->addCameraSceneNode(0, ptr->position, ptr->rotation);
        }
    }
}

void is::systems::CameraSystem::start()
{

}

void is::systems::CameraSystem::update()
{
    
}

void is::systems::CameraSystem::stop()
{

}

void is::systems::CameraSystem::onTearDown()
{

}

