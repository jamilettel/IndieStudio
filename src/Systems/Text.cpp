/*
** EPITECH PROJECT, 2020
** Systems/TextSystem.cpp
** File description:
** 
*/

#include "Systems/Text.hpp"
#include "Components/Text.hpp"

#include <algorithm>
#include <iostream>

using namespace is::systems;
using namespace is::components;

void TextSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(TextComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<TextComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("TextSystem", "Could not getTextComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [&ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("TextComponent", "Could not find window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->init(window);
    }
}

void TextSystem::start()
{
}

void TextSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(TextComponent).hash_code())) {
        const auto &ptr = static_cast<TextComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("TextSystem", "Could not getTextComponent pointer");
        ptr->updateText();
    }
}

void TextSystem::stop()
{
}

void TextSystem::onTearDown()
{
}

