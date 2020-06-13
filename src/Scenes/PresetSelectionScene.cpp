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
    _systemManager->addSystem(std::make_shared<AudioSystem>());
}

void PresetSelectionScene::initEntities()
{
    int i = 1;
    auto &rulesComponents = _componentManager->getComponentsByType(typeid(is::components::RulesComponent).hash_code());
    auto &characterComponents = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());

    if (rulesComponents.empty())
        throw is::exceptions::ECSException("Rules Component Missing for Preset Selection Scene.");

    for (auto &component : characterComponents) {
        const auto &c = std::static_pointer_cast<is::components::CharacterComponent>(component);
        const auto &r = std::static_pointer_cast<is::components::RulesComponent>(rulesComponents[0]);
        if (c->characterType != components::CharacterComponent::AI) {
            c->characterType = components::CharacterComponent::AI;
            c->presetNumber = -1;
            c->joystickId = -1;
            r->setAiLevel(i, 1);
        }
        i++;
    }
    initEntity(prefabs::GlobalPrefabs::createPresetSelection(*_componentManager), false);
}
