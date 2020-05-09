/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Game.hpp"


bool is::Game::isRunning = true;
is::ecs::Scenes is::Game::currentScene = is::ecs::NOTHING;

void is::Game::addScene(is::ecs::Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene)
{
    _scenes[sceneType] = scene;
}

void is::Game::launchGame(is::ecs::Scenes startScene)
{
    currentScene = startScene;
    changeScene = startScene;
    _scenes[currentScene]->awake();
    _scenes[currentScene]->start();
    while (isRunning) {
        _scenes[currentScene]->update();
        if (currentScene != changeScene) {
            _scenes[changeScene]->stop();
            _scenes[changeScene]->onTearDown();
            _scenes[currentScene]->awake();
            _scenes[currentScene]->start();
            changeScene = currentScene;
        }
    }
    _scenes[currentScene]->stop();
    _scenes[currentScene]->onTearDown();
}

void is::Game::setActualScene(is::ecs::Scenes scene)
{
    currentScene = scene;
}
