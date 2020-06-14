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
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createSound("sounds/time_over.wav"), false);

    _timeOverSound.emplace(*entity->getComponent<AudioComponent>()->get());
    _timeOverSound->get().init();
    entity->setInit(true);

    auto &entity2 = initRuntimeEntity(prefabs::GlobalPrefabs::createSound("sounds/game_start.wav"), false);

    _gameStartSound.emplace(*entity2->getComponent<AudioComponent>()->get());
    _gameStartSound->get().init();
    entity2->setInit(true);
}

void EndGameSystem::start()
{
}

void EndGameSystem::update()
{
    const auto &characterComponents = _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code());
    int count = 0;
    const RulesComponent &rules = *static_cast<RulesComponent*>(_componentManager->getComponentsByType(typeid(RulesComponent).hash_code())[0].get());

    if (!_gsAlreadyPlaying) {
        _gameStartSound.value().get().toPlay();
        _gsAlreadyPlaying = true;
    }
    for (auto &elem : characterComponents) {
        const auto &ptr = static_cast<is::components::CharacterControllerComponent*>(elem.get());
        count += ptr->isDead;
    }

    for (auto &elem: characterComponents) {
        const auto &ptr = static_cast<is::components::CharacterControllerComponent*>(elem.get());
    
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
        const TimerComponent &timer = *static_cast<TimerComponent *>(elem.get());

        if (timer.getTime() <= 1 && !_toAlreadyPlaying) {
            _timeOverSound.value().get().toPlay();
            _toAlreadyPlaying = true;
        }
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

