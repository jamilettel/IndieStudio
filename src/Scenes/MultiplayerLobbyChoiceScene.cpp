/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MultiplayerLobbyChoiceScene.hpp"

is::scenes::MultiplayerLobbyChoiceScene::MultiplayerLobbyChoiceScene() :
AScene(is::ecs::Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::MultiplayerLobbyChoiceScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::NetworkSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
}

void is::scenes::MultiplayerLobbyChoiceScene::initEntities()
{
    auto e = _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())[0];
    const auto &ptr = std::static_pointer_cast<is::components::NetworkComponent>(e);
    initEntity(prefabs::GlobalPrefabs::createMultiplayerLobbyChoice(ptr), false);
}
