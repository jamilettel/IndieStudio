/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemLight
*/

#include "Systems/Light.hpp"

using namespace irr;

void is::systems::SystemLight::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentLight).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentLight>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemLight", "Could not get ComponentLight pointer");

        std::shared_ptr<is::components::ComponentWindow> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::ComponentWindow>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("SystemLight", "Could not get ComponentWindow pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("SystemLight", "Could not found window");
        ptr_window->scenemgr->addLightSceneNode(nullptr, ptr->position, ptr->color, ptr->radius);
    }
}

void is::systems::SystemLight::start()
{

}

void is::systems::SystemLight::update()
{

}

void is::systems::SystemLight::stop()
{

}

void is::systems::SystemLight::onTearDown()
{

}

