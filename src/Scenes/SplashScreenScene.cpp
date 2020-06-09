/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/SplashScreenScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

SplashScreenScene::SplashScreenScene() :
AScene(Scenes::SCENE_SPLASH_SCREEN)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void SplashScreenScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
}

void SplashScreenScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab(), true);
    initEntity(prefabs::GlobalPrefabs::createSplashScreen(), false);
    initEntity(prefabs::GlobalPrefabs::createCharacter(), true);
    initEntity(prefabs::GlobalPrefabs::createPresets(), true);
    initEntity(prefabs::GlobalPrefabs::createRules(), true);
}

void SplashScreenScene::start()
{
    AScene::start();
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void SplashScreenScene::update()
{
    AScene::update();
    if (_time->get().getElapsedTime() > 3000) {
        is::Game::setActualScene(SCENE_MULTIPLAYER_RULE_SETTINGS);
        return;
    }
}
