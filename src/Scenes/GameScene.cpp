/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

is::scenes::GameScene::GameScene() :
AScene()
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager);
}

void is::scenes::GameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::SystemWindow>());
    _systemManager->addSystem(std::make_shared<is::systems::SystemCamera>());
    _systemManager->addSystem(std::make_shared<is::systems::SystemModelRenderer>());
    _systemManager->addSystem(std::make_shared<is::systems::SystemCharacterController>());
    _systemManager->addSystem(std::make_shared<is::systems::SystemLight>());
    _systemManager->addSystem(std::make_shared<is::systems::SystemAudio>());
    _systemManager->addSystem(std::make_shared<is::systems::MovementSystem>());
}

void is::scenes::GameScene::initEntities()
{
    MapGenerator mg;

    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab());
    mg.generateMap(*this);
    initEntity(prefabs::GlobalPrefabs::createPlayer());
}
