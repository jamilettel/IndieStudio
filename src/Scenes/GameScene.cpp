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
    _systemManager->addSystem(std::make_shared<SystemCamera>());
    _systemManager->addSystem(std::make_shared<SystemModelRenderer>());
    _systemManager->addSystem(std::make_shared<SystemCharacterController>());
}

void GameScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab());
    for (int i = -4; i < 4; i++) {
        for (int j = -4; j < 4; j++) {
            initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(i * 3, -3, j * 3)));
        }
    }
    initEntity(prefabs::GlobalPrefabs::createPlayer());
}
