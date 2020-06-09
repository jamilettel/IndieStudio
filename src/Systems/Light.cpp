/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** LightSystem
*/

#include "Systems/Light.hpp"

using namespace irr;
using namespace is::components;

void is::systems::LightSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::LightComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<is::components::LightComponent*>(elem.get());

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("LightSystem", "Could not get WindowComponent pointer");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        irr::scene::ILightSceneNode *light = window->scenemgr->addLightSceneNode(nullptr, ptr->position, ptr->color, ptr->radius);
        light->enableCastShadow();
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

