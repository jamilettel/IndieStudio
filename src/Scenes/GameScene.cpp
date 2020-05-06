/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

GameScene::GameScene() : AScene()
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager);
}

GameScene::~GameScene()
{
}

void GameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<SystemWindow>());
}

void GameScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab());
}
