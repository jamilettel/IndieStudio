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
    RulesComponent &rules = *std::static_pointer_cast<RulesComponent>(_componentManager->getComponentsByType(typeid(RulesComponent).hash_code())[0]);

    for (auto &elem : characterComponents) {
        auto ptr = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(elem);
        count += ptr->isDead;
    }

    for (auto &elem: characterComponents) {
        auto ptr = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(elem);
    
        if (ptr->isDead && ptr->getCharacterComponent().getPosition() == 1) {
            ptr->getCharacterComponent().setPosition(rules.getNumberOfPlayers() - count + 1);
        }
    }

    if (count >= rules.getNumberOfPlayers() - 1) {
        is::Game::setActualScene(is::ecs::SCENE_ENDGAME);
        return;
    }

    auto &timers = _componentManager->getComponentsByType(typeid(TimerComponent).hash_code());

    for (auto &elem : timers) {
        TimerComponent &timer = *std::static_pointer_cast<TimerComponent>(elem);

        if (timer.getTime() <= 0)
            is::Game::setActualScene(is::ecs::SCENE_ENDGAME);
    }
}

void EndGameSystem::stop()
{
}

void EndGameSystem::onTearDown()
{
}

