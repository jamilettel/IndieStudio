/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MultiplayerGameScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

MultiplayerGameScene::MultiplayerGameScene() :
AScene(Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void MultiplayerGameScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<AIControllerLevel5System>());
    _systemManager->addSystem(std::make_shared<ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<NetworkSystem>());
    _systemManager->addSystem(std::make_shared<NetworkInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());

}

void MultiplayerGameScene::initEntities()
{
    auto characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    MapGenerator mg;

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    mg.generateMap(*this, 1, 15, 13);
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[0].get()),
        *_componentManager.get(),
        "player_white.png"
    ));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[1].get()),
        *_componentManager.get(),
        "player_black.png"
    ));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[2].get()),
        *_componentManager.get(),
        "player_blue.png"
    ));
    initEntity(prefabs::GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[3].get()),
        *_componentManager.get(),
        "player_red.png"
    ));
}

void MultiplayerGameScene::awake()
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

void MultiplayerGameScene::onTearDown()
{
    AScene::onTearDown();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.removeEventKeyReleased(irr::EKEY_CODE::KEY_KEY_P);
    }
}
