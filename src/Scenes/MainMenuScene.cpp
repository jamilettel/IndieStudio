/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "Scenes/MainMenuScene.hpp"

is::scenes::MainMenuScene::MainMenuScene() : AScene()
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::MainMenuScene::initSystems()
{

}

void is::scenes::MainMenuScene::initEntities()
{

}

