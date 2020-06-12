
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/ControllersScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

ControllersScene::ControllersScene() :
AScene(Scenes::SCENE_CONTROLLERS)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void ControllersScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<PresetSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
}

void ControllersScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createControllersBase(), false);
    initEntity(prefabs::GlobalPrefabs::createControllersOptions(*_componentManager), false);
}
