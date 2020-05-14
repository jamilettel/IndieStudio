/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "Systems/Time.hpp"

using namespace is::systems;
using namespace is::ecs;

void TimeSystem::awake()
{
}

void TimeSystem::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<is::components::TimeComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("TimeSystem", "Could not get TimeComponent pointer");
        ptr->start();
    }
}

void TimeSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code())) {
        auto ptr = dynamic_cast<is::components::TimeComponent *>(elem.get());
        ptr->update();
    }
}

void TimeSystem::stop()
{
}

void TimeSystem::onTearDown()
{
}
