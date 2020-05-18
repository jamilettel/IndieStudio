/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/SplashScreenScene.hpp"

is::scenes::SplashScreenScene::SplashScreenScene() :
AScene(is::ecs::Scenes::SCENE_SPLASH_SCREEN)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::SplashScreenScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
}

void is::scenes::SplashScreenScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createGlobalPrefab(), true);
    initEntity(prefabs::GlobalPrefabs::createSplashScreen(), false);
}

void is::scenes::SplashScreenScene::start()
{
    AScene::start();
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void is::scenes::SplashScreenScene::update()
{
    AScene::update();
    if (_time->get().getElapsedTime() > 3000) {
        is::Game::setActualScene(is::ecs::SCENE_PAUSE);
        return;
    }
}
