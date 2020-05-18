/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** LightSystem
*/

#include "Systems/Light.hpp"

using namespace irr;

void is::systems::LightSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::LightComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<is::components::LightComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("LightSystem", "Could not get LightComponent pointer");

        std::shared_ptr<is::components::WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("LightSystem", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("LightSystem", "Could not find window");
        ptr_window->scenemgr->addLightSceneNode(nullptr, ptr->position, ptr->color, ptr->radius);
    }
}

void is::systems::LightSystem::start()
{

}

void is::systems::LightSystem::update()
{

}

void is::systems::LightSystem::stop()
{

}

void is::systems::LightSystem::onTearDown()
{

}

