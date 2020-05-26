/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MultiplayerGameScene.hpp"

using namespace is::prefabs;
using namespace is::scenes;

is::scenes::MultiplayerGameScene::MultiplayerGameScene() :
AScene(is::ecs::Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::MultiplayerGameScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::NetworkSystem>());

}

void is::scenes::MultiplayerGameScene::initEntities()
{
    auto characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    MapGenerator mg;

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    mg.generateMap(*this, 1, 15, 13);
    // initEntity(GlobalPrefabs::createPlayer(irr::core::vector3df(-5 * 3, 0, 6 * 3)));
    initEntity(GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[0].get()),
        *_componentManager.get()
    ));
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(-5 * 3, 0, -6 * 3)));
    initEntity(GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(-5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[1].get()),
        *_componentManager.get())
    );
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(5 * 3, 0, -6 * 3)));
    initEntity(GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, -6 * 3),
        *static_cast<CharacterComponent *>(characters[2].get()),
        *_componentManager.get()
    ));
    // initEntity(GlobalPrefabs::createAI(irr::core::vector3df(5 * 3, 0, 6 * 3)));
    initEntity(GlobalPrefabs::createBombermanCharacter(
        irr::core::vector3df(5 * 3, 0, 6 * 3),
        *static_cast<CharacterComponent *>(characters[3].get()),
        *_componentManager.get()
    ));
}

void is::scenes::MultiplayerGameScene::awake()
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

void is::scenes::MultiplayerGameScene::onTearDown()
{
    AScene::onTearDown();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.removeEventKeyReleased(EKEY_CODE::KEY_KEY_P);
    }
}
