/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Time System
*/

#include "Systems/Time.hpp"

using namespace is::systems;
using namespace is::ecs;

void TimeSystem::awake()
{
}

void TimeSystem::start()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<is::components::TimeComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("TimeSystem", "Could not get TimeComponent pointer");
        ptr->start();
    }
}

void TimeSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::TimeComponent *>(elem.get());
        ptr->update();
    }
}

void TimeSystem::stop()
{
}

void TimeSystem::onTearDown()
{
}
