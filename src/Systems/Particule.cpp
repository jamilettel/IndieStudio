/*
** EPITECH PROJECT, 2020
** Systems/ParticuleSystem.cpp
** File description:
** 
*/

#include "Systems/Particule.hpp"
#include "Components/Particule.hpp"
#include <algorithm>

using namespace is::systems;
using namespace is::components;

void ParticuleSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(ParticuleComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<ParticuleComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("ParticuleSystem", "Could not getParticuleComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("ParticuleComponent", "Could not found window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->init(window);
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

