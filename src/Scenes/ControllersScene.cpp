/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/ControllersScene.hpp"

is::scenes::ControllersScene::ControllersScene() :
AScene(is::ecs::Scenes::SCENE_CONTROLLERS)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::ControllersScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
}

void is::scenes::ControllersScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createControllers(), false);
}