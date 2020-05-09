/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Systems/Image.hpp"
#include "Systems/Window.hpp"
#include "Scenes/MainMenuScene.hpp"

is::scenes::MainMenuScene::MainMenuScene() : AScene()
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::MainMenuScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
}

void is::scenes::MainMenuScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab());
    initEntity(prefabs::GlobalPrefabs::createMainMenu());
}

