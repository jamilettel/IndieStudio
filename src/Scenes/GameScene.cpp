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
    _systemManager->addSystem(std::make_shared<SystemGravity>());
}

void GameScene::initEntities()
{
    std::shared_ptr<is::ecs::Entity> a = std::make_shared<is::ecs::Entity>();

    a->addComponent<ComponentGravity>(a);
    initEntity(a);
}
