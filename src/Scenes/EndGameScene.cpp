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
    {
        const double posX[] = {2.5, 26.3, 51.3, 76.3};

        for (size_t i = 0; i < 4; i++)
            initEntity(prefabs::EndGamePrefabs::createWindow(posX[i]), false);
    }

    {
        const int posX[] = {40, 420, 820, 1220};

        for (size_t i = 0; i < 4; i++)
            initEntity(prefabs::EndGamePrefabs::createContinueButton(posX[i]), false);
    };
    
    {
        const int posX[] = {80, 450, 850, 1250};

        for (size_t i = 0; i < 4; i++)
            initEntity(prefabs::EndGamePrefabs::createBackwardButton(posX[i]), false);
    };
    
    {
        const int posX[] = {280, 670, 1070, 1470};

        for (size_t i = 0; i < 4; i++) {
            initEntity(prefabs::EndGamePrefabs::createForwardButton(posX[i]), false);
        }
    };

    {
        const double posX[] = {3.5, 27.2, 52.2, 77.2};

        for (size_t i = 0; i < 4; i++) {
            initEntity(prefabs::EndGamePrefabs::createHighTable(posX[i]), false);
            initEntity(prefabs::EndGamePrefabs::createLowTable(posX[i]), false);
        }
    };

    {
        initEntity(prefabs::EndGamePrefabs::createMedal1(10), false);
        initEntity(prefabs::EndGamePrefabs::createMedal2(34), false);
        initEntity(prefabs::EndGamePrefabs::createMedal3(58), false);
    }

    {
        initEntity(prefabs::EndGamePrefabs::createTextHigh(), false);
        initEntity(prefabs::EndGamePrefabs::createTextLow(), false);
    }
}
