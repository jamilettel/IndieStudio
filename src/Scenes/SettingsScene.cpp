/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/SettingsScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

SettingsScene::SettingsScene() :
AScene(Scenes::SCENE_SETTINGS)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void SettingsScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<SettingsLoaderSystem>());
    if (is::Game::getPreviousScene() == SCENE_PAUSE) {
        _systemManager->addSystem(std::make_shared<PauseSystem>());
        _systemManager->addSystem(std::make_shared<KeyboardInputSystem>());
    }
    _systemManager->addSystem(std::make_shared<AudioSystem>());
}

void SettingsScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createSettings(), false);

    if (is::Game::getPreviousScene() == SCENE_PAUSE) {
        auto &characters = _componentManager->getComponentsByType(
            typeid(is::components::CharacterComponent).hash_code());

        for (auto character : characters) {
            auto ptr = static_cast<is::components::CharacterComponent *>(character.get());

            initEntity(prefabs::GlobalPrefabs::createPauseController(*ptr, *_componentManager.get()), false);
        }
        initEntity(prefabs::GlobalPrefabs::createGlobalPause());
    }
}
