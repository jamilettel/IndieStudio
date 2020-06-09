/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/PauseScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

PauseScene::PauseScene() :
AScene(Scenes::SCENE_PAUSE)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void PauseScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<KeyboardInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<PauseSystem>());
}

void PauseScene::initEntities()
{
    auto &characters = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());

    initEntity(prefabs::GlobalPrefabs::createPause(), false);
    for (auto character : characters) {
        auto ptr = static_cast<is::components::CharacterComponent*>(character.get());

        initEntity(prefabs::GlobalPrefabs::createPauseController(*ptr, *_componentManager.get()), false);
    }
}
