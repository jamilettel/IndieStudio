/*
** EPITECH PROJECT, 2020
** Systems/Pause.cpp
** File description:
** Pause System
*/

#include "Systems/Pause.hpp"
#include "Game.hpp"
#include "Components/Cursor.hpp"

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
    auto &cursors = _componentManager->getComponentsByType(typeid(is::components::CursorComponent).hash_code());

    for (auto &cursor: cursors) {
        auto ptr = static_cast<is::components::CursorComponent *>(cursor.get());
        ptr->visible = !ptr->visible;
    }
}

void PauseSystem::update()
{
    static bool canChange = false;
    bool click = false;

    for (const auto &p : _inputManagers) {
        const auto &im = static_cast<is::components::InputManagerComponent*>(p.get());
        if (!im->isActionSet("Pause"))
            continue;
        if (im->getInput("Pause")) {
            click = true;
            if (canChange) {
                if (is::Game::getCurrentScene() == is::ecs::SCENE_GAME) {
                    auto es = _componentManager->getComponentsByType(typeid(AudioComponent).hash_code());

                    std::for_each(es.begin(), es.end(), [](std::shared_ptr<Component> &c) {
                        AudioComponent &audio = *static_cast<AudioComponent *>(c.get());

                        audio.pause();
                    });
                    is::Game::setActualScene(is::ecs::SCENE_PAUSE, true, false);
                } else
                    is::Game::setActualScene(is::ecs::SCENE_GAME, false, true);
            }
            break;
        }
        im->resetValue("Pause");
    }
    canChange = !click;
}

void PauseSystem::stop()
{
    auto &cursors = _componentManager->getComponentsByType(typeid(is::components::CursorComponent).hash_code());

    for (auto &cursor: cursors) {
        auto ptr = static_cast<is::components::CursorComponent *>(cursor.get());
        ptr->visible = !ptr->visible;
    }
}

void PauseSystem::onTearDown()
{
}
