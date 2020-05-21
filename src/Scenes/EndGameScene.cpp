/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndEndGameScene
*/

#include "Scenes/EndGameScene.hpp"

is::scenes::EndGameScene::EndGameScene() :
AScene(is::ecs::Scenes::SCENE_ENDGAME)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::EndGameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    // _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextureSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
}

void is::scenes::EndGameScene::initEntities()
{
    initEntity(prefabs::EndGamePrefabs::createBackground(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer2(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer3(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer4(), false);
    initEntity(prefabs::EndGamePrefabs::createWindow(), false);
    initEntity(prefabs::EndGamePrefabs::createWindow2(), false);
    initEntity(prefabs::EndGamePrefabs::createWindow3(), false);
    initEntity(prefabs::EndGamePrefabs::createWindow4(), false);
    initEntity(prefabs::EndGamePrefabs::createContinueButton(), false);
    initEntity(prefabs::EndGamePrefabs::createContinueButton2(), false);
    initEntity(prefabs::EndGamePrefabs::createContinueButton3(), false);
    initEntity(prefabs::EndGamePrefabs::createContinueButton4(), false);
    initEntity(prefabs::EndGamePrefabs::createBackwardButton(), false);
    initEntity(prefabs::EndGamePrefabs::createForwardButton(), false);
    initEntity(prefabs::EndGamePrefabs::createText(), false);
}
