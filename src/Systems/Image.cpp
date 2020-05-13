/*
** EPITECH PROJECT, 2020
** Systems/ImageSystem.cpp
** File description:
** 
*/

#include "Systems/Image.hpp"
#include "Components/Image.hpp"

#include <algorithm>
#include <iostream>

using namespace is::systems;
using namespace is::components;

//
#include <irrlicht.h>
//

void ImageSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ImageComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ImageComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ImageSystem", "Could not getImageComponent pointer");
        
        std::shared_ptr<WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("ImageComponent", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("ImageComponent", "Could not found window");

        ptr->init(ptr_window);
    }
}

void ImageSystem::start()
{
}

void ImageSystem::update()
{
}

void ImageSystem::stop()
{
}

void ImageSystem::onTearDown()
{
}

