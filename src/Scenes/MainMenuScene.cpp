/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MainMenuScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

MainMenuScene::MainMenuScene() :
AScene(is::ecs::Scenes::SCENE_MAIN_MENU)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void MainMenuScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
}

void MainMenuScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createMainMenu(), false);
    initEntity(prefabs::GlobalPrefabs::createMainMusic(), false);
}
