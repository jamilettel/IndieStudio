/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Game.hpp"


bool is::Game::isRunning = true;
is::ecs::Scenes is::Game::currentScene = is::ecs::NOTHING;
is::ecs::Scenes is::Game::_previousScene = is::ecs::NOTHING;

void is::Game::addScene(is::ecs::Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene)
{
    _scenes[sceneType] = scene;
}

void is::Game::switchScene()
{
    _scenes[changeScene]->stop();
    _scenes[changeScene]->onTearDown();
    _scenes[currentScene]->awake();
    _scenes[currentScene]->start();
    changeScene = currentScene;
}

void is::Game::launchGame(is::ecs::Scenes startScene)
{
    currentScene = startScene;
    changeScene = startScene;
    _previousScene = startScene;
    _scenes[currentScene]->awake();
    _scenes[currentScene]->start();
    while (isRunning) {
        _scenes[currentScene]->update();
        if (currentScene != changeScene)
            switchScene();
    }
    _scenes[currentScene]->stop();
    _scenes[currentScene]->onTearDown();
}

void is::Game::setActualScene(is::ecs::Scenes scene)
{
    _previousScene = currentScene;
    currentScene = scene;
}

is::ecs::Scenes is::Game::getPreviousScene()
{
    return _previousScene;
}

is::ecs::Scenes is::Game::getCurrentScene()
{
    return currentScene;
}
