/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Texture
*/

#include "Systems/Texture.hpp"
#include "Components/Texture.hpp"

#include <algorithm>
#include <iostream>

using namespace is::systems;
using namespace is::components;

#include <irrlicht/irrlicht.h>

void TextureSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(TextureComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<is::components::TextureComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get ModelRendererComponent pointer");

        std::shared_ptr<is::components::WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("ModelRendererSystem", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not find window");
        ptr->init(ptr_window);
    }
}

void TextureSystem::start()
{
}

void TextureSystem::update()
{
}

void TextureSystem::stop()
{
}

void TextureSystem::onTearDown()
{
}

