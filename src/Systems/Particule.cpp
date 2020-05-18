/*
** EPITECH PROJECT, 2020
** Systems/ParticuleSystem.cpp
** File description:
** 
*/

#include "Systems/Particule.hpp"
#include "Components/Particule.hpp"

#include <algorithm>
#include <iostream>

using namespace is::systems;
using namespace is::components;

void ParticuleSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ParticuleComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<ParticuleComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ParticuleSystem", "Could not getParticuleComponent pointer");
        
        std::shared_ptr<WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("ParticuleComponent", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("ParticuleComponent", "Could not found window");

        ptr->init(ptr_window);
    }
}

void ParticuleSystem::start()
{
}

void ParticuleSystem::update()
{
}

void ParticuleSystem::stop()
{
}

void ParticuleSystem::onTearDown()
{
}

