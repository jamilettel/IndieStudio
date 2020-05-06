/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCamera
*/

#include "Systems/Camera.hpp"

using namespace irr;

void is::systems::SystemCamera::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentCamera).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentCamera>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCamera", "Could not get ComponentCamera pointer");
        for (auto &cw : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
            auto ptr_window = std::dynamic_pointer_cast<is::components::ComponentWindow>(cw);
            if (!ptr_window)
                throw new is::exceptions::Exception("SystemCamera", "Could not get ComponentWindow pointer");
            if (ptr->windowName != ptr_window->windowName)
                continue;
            ptr_window->scenemgr->addCameraSceneNode(0, ptr->position, ptr->rotation);
        }
    }
}

void is::systems::SystemCamera::start()
{

}

void is::systems::SystemCamera::update()
{
    
}

void is::systems::SystemCamera::stop()
{

}

void is::systems::SystemCamera::onTearDown()
{

}

