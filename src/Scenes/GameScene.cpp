/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

is::scenes::GameScene::GameScene() :
AScene(is::ecs::Scenes::SCENE_GAME)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::GameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::KeyboardInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CharacterControllerSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::GravitySystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JumpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::MovementSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::BombSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::FireSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::SliderSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::PowerUpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerSystem>());
}

void is::scenes::GameScene::initEntities()
{
    MapGenerator mg;

    mg.generateMap(*this);
    initEntity(prefabs::GlobalPrefabs::createPlayer());
    initEntity(prefabs::GlobalPrefabs::createAI());
    initEntity(prefabs::GlobalPrefabs::createCanvas());
}
