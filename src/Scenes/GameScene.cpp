/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

using namespace is::prefabs;
using namespace is::scenes;

GameScene::GameScene() :
AScene(is::ecs::Scenes::SCENE_GAME)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void GameScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<is::systems::JumpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::GravitySystem>());
    _systemManager->addSystem(std::make_shared<is::systems::MovementSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::BombSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::FireSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::SliderSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::PowerUpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel1System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel2System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel3System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel4System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel5System>());
    _systemManager->addSystem(std::make_shared<is::systems::ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::EndGameSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextureSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TimerSystem>());
}

void GameScene::initEntities()
{
    auto &characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    auto &rules = getRulesComponent();
    MapGenerator mg;
    std::vector<std::shared_ptr<is::ecs::Component>> a;

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    mg.generateMap(*this, 1, 15, 13, a);

    for (int i = 0; i < rules.getNumberOfPlayers() && i != 4; i++) {
        switch (i)
        {
        case 0:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(-5 * 3, 0, 6 * 3),
                *static_cast<CharacterComponent *>(characters[0].get()),
                *_componentManager.get(),
                "player_white.png",
                rules.getAiLevels()[0]
            ));
            break;
        case 1:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(5 * 3, 0, -6 * 3),
                *static_cast<CharacterComponent *>(characters[2].get()),
                *_componentManager.get(),
                "player_blue.png",
                rules.getAiLevels()[2]
            ));
            break;
        case 2:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(-5 * 3, 0, -6 * 3),
                *static_cast<CharacterComponent *>(characters[1].get()),
                *_componentManager.get(),
                "player_black.png",
                rules.getAiLevels()[1]
            ));
            break;
        case 3:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(5 * 3, 0, 6 * 3),
                *static_cast<CharacterComponent *>(characters[3].get()),
                *_componentManager.get(),
                "player_red.png",
                rules.getAiLevels()[3]
            ));
            break;
        default:
            break;
        }
    }

    initEntity(GlobalPrefabs::createTimer(rules));
}

void GameScene::awake()
{
    AScene::awake();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.addEventKeyReleased(EKEY_CODE::KEY_KEY_P, []() {
            if (is::Game::getCurrentScene() == is::ecs::SCENE_GAME)
                is::Game::setActualScene(is::ecs::SCENE_PAUSE);
            else if (is::Game::getCurrentScene() == is::ecs::SCENE_PAUSE)
                is::Game::setActualScene(is::ecs::SCENE_GAME);
        });
    }
}

void GameScene::onTearDown()
{
    AScene::onTearDown();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.removeEventKeyReleased(EKEY_CODE::KEY_KEY_P);
    }
}

RulesComponent &GameScene::getRulesComponent() const
{
    auto entities = is::ecs::AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}