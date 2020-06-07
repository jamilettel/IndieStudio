/*
** EPITECH PROJECT, 2020
** Systems/Pause.cpp
** File description:
** Pause System
*/

#include "Systems/Pause.hpp"
#include "Game.hpp"

using namespace is::systems;

void PauseSystem::awake()
{
    _inputManagers = _componentManager->getComponentsByType(typeid(is::components::InputManagerComponent).hash_code());

    if (_inputManagers.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "InputManager component required for Pause System");
}

void PauseSystem::start()
{
}

void PauseSystem::update()
{
    for (const auto &p : _inputManagers) {
        const auto &im = static_cast<is::components::InputManagerComponent*>(p.get());
        if (!im->isActionSet("Pause"))
            continue;
        if (im->getInput("Pause") != 0) {
            if (is::Game::getCurrentScene() == is::ecs::SCENE_GAME)
                is::Game::setActualScene(is::ecs::SCENE_PAUSE, true, false);
            else if (is::Game::getCurrentScene() == is::ecs::SCENE_PAUSE)
                is::Game::setActualScene(is::ecs::SCENE_GAME, false, true);
        }
        im->resetValue("Pause");
    }
}

void PauseSystem::stop()
{
}

void PauseSystem::onTearDown()
{
}

