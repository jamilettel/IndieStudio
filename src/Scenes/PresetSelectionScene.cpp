/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/PresetSelectionScene.hpp"

is::scenes::PresetSelectionScene::PresetSelectionScene() :
AScene(is::ecs::Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::PresetSelectionScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
}

void is::scenes::PresetSelectionScene::initEntities()
{
    initEntity(prefabs::GlobalPrefabs::createPresetSelectionBase(), false);
    initEntity(prefabs::GlobalPrefabs::createPresetSelectionOptions(*_componentManager), false);
}

void is::scenes::PresetSelectionScene::awake()
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
