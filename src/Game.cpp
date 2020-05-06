/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Game.hpp"

bool is::Game::isRunning = true;

void is::Game::addScene(Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene)
{
    _scenes[sceneType] = scene;
}

void is::Game::launchGame(Scenes startScene)
{
    currentScene = startScene;
    _scenes[currentScene]->awake();
    _scenes[currentScene]->start();
    while (isRunning) {
        _scenes[currentScene]->update();
    }
    _scenes[currentScene]->stop();
    _scenes[currentScene]->onTearDown();
}
