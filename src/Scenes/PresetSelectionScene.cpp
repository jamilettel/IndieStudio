/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/PresetSelectionScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

PresetSelectionScene::PresetSelectionScene() :
AScene(Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void PresetSelectionScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<AlertSystem>());
}

void PresetSelectionScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createPresetSelectionBase(), false);
    initEntity(prefabs::GlobalPrefabs::createPresetSelectionOptions(*_componentManager), false);
}

void PresetSelectionScene::awake()
{
    AScene::awake();
    auto &rulesComponents = _componentManager->getComponentsByType(typeid(is::components::RulesComponent).hash_code());
    for (auto &component : rulesComponents) {
        auto *c = static_cast<is::components::RulesComponent*>(component.get());
        c->setAiLevel(1, 1);
        c->setAiLevel(2, 1);
        c->setAiLevel(3, 1);
        c->setAiLevel(4, 1);
        c->setAiLevel(5, 1);
    }
    auto &characterComponents = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());
    for (auto &component : characterComponents) {
        auto *c = static_cast<is::components::CharacterComponent*>(component.get());
        c->characterType = components::CharacterComponent::AI;
        c->presetNumber = -1;
    }
}
