/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Hud
*/

#include "Systems/Hud.hpp"

using namespace is::systems;

void HudSystem::awake()
{
}

void HudSystem::start()
{
}

void HudSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::HudComponent).hash_code())) {
        auto ptr = static_cast<is::components::HudComponent *>(elem.get());
        ptr->update();
    }
}

void HudSystem::stop()
{
}

void HudSystem::onTearDown()
{
}
