/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MultiplayerHubScene.hpp"

is::scenes::MultiplayerHubScene::MultiplayerHubScene() :
AScene(is::ecs::Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::MultiplayerHubScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<is::systems::NetworkSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
}

void is::scenes::MultiplayerHubScene::initEntities()
{
    std::shared_ptr<is::ecs::Entity> &e = initEntity(prefabs::GlobalPrefabs::createGlobalPrefabMultiplayer(), true);
    auto a = e->getComponent<is::components::NetworkComponent>();
    initEntity(prefabs::GlobalPrefabs::createMultiplayerHub(*e->getComponent<is::components::NetworkComponent>()), false);
}
