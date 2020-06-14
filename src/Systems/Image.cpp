/*
** EPITECH PROJECT, 2020
** Systems/ImageSystem.cpp
** File description:
** 
*/

#include "Systems/Image.hpp"
#include "Components/Image.hpp"
#include <algorithm>

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

//
#include <irrlicht.h>
//

void ImageSystem::awake()
{
    const auto &images = _componentManager->getComponentsByType(typeid(ImageComponent).hash_code());

    for (const auto &elem : images) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<ImageComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("ImageSystem", "Could not getImageComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("ImageComponent", "Could not get WindowComponent pointer");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->init(window);
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

