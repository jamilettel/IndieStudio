/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

GameScene::GameScene() : AScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initSystems()
{
    _systemManager.addSystem(std::make_shared<Gravity>());
}