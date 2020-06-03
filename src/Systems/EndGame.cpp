/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndGame
*/

#include "Systems/EndGame.hpp"

using namespace is::ecs;
using namespace is::components;
using namespace is::systems;

void EndGameSystem::awake()
{
}

void EndGameSystem::start()
{
}

void EndGameSystem::update()
{
    std::vector<std::shared_ptr<Component>> &characterComponents = _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code());
    int count = 0;

    for (auto &elem : characterComponents) {
        auto ptr = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(elem);
        count += ptr->isDead;
    }
    
    if (count >= 3) {
        is::Game::setActualScene(is::ecs::SCENE_ENDGAME);
        return;
    }
}

void EndGameSystem::stop()
{
}

void EndGameSystem::onTearDown()
{
}

