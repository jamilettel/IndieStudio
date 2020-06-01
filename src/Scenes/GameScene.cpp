/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

GameScene::GameScene() :
AScene(Scenes::SCENE_GAME)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void GameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<KeyboardInputSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<CharacterControllerSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
    _systemManager->addSystem(std::make_shared<JumpSystem>());
    _systemManager->addSystem(std::make_shared<GravitySystem>());
    _systemManager->addSystem(std::make_shared<MovementSystem>());
    _systemManager->addSystem(std::make_shared<BombSystem>());
    _systemManager->addSystem(std::make_shared<FireSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<SliderSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<PowerUpSystem>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel1System>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel2System>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel3System>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel4System>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel5System>());
    _systemManager->addSystem(std::make_shared<ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<EndGameSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
}

void GameScene::initEntities()
{
    auto &characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    auto &rules = getRulesComponent();
    MapGenerator mg;

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    mg.generateMap(*this, 1, 15, 13);
    // initEntity(GlobalPrefabs::createPlayer(irr::core::vector3df(-5 * 3, 0, 6 * 3)));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[0].get()),
        *_componentManager.get(),
        "player_white.png",
        rules.getAiLevels()[0]
    ));
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(-5 * 3, 0, -6 * 3)));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[1].get()),
        *_componentManager.get(),
        "player_black.png",
        rules.getAiLevels()[1]
    ));
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(5 * 3, 0, -6 * 3)));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[2].get()),
        *_componentManager.get(),
        "player_blue.png",
        rules.getAiLevels()[2]
    ));
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(5 * 3, 0, 6 * 3)));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[3].get()),
        *_componentManager.get(),
        "player_red.png",
        rules.getAiLevels()[3]
    ));
}

void GameScene::awake()
{
    AScene::awake();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.addEventKeyReleased(irr::EKEY_CODE::KEY_KEY_P, []() {
            if (is::Game::getCurrentScene() == SCENE_GAME)
                is::Game::setActualScene(SCENE_PAUSE);
            else if (is::Game::getCurrentScene() == SCENE_PAUSE)
                is::Game::setActualScene(SCENE_GAME);
        });
    }
}

void GameScene::onTearDown()
{
    AScene::onTearDown();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.removeEventKeyReleased(irr::EKEY_CODE::KEY_KEY_P);
    }
}

RulesComponent &GameScene::getRulesComponent() const
{
    auto entities = AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}