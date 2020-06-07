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

#include <irrlicht.h>

void TextureSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(TextureComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<is::components::TextureComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("TextSystem", "Could not get TextComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [&ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("TextSystem", "Could not find window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->init(window);
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

