/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/RecordScene.hpp"

is::scenes::RecordScene::RecordScene() :
AScene(is::ecs::Scenes::SCENE_RECORD)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::RecordScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
}

void is::scenes::RecordScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createRecord(), false);
}