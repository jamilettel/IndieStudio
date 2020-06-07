/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Timer
*/

#include "Systems/Timer.hpp"

using namespace is::systems;

void TimerSystem::awake()
{
}

void TimerSystem::start()
{
}

void TimerSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::TimerComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::TimerComponent *>(elem.get());
        ptr->update();
    }
}

void TimerSystem::stop()
{
}

void TimerSystem::onTearDown()
{
}
