/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** MultiplayerRuleSettingsScene
*/

#include "Scenes/MultiplayerRuleSettingsScene.hpp"

using namespace is::scenes;
using namespace is::components;
using namespace is::systems;
using namespace is::ecs;

MultiplayerRuleSettingsScene::MultiplayerRuleSettingsScene() : AScene(Scenes::SCENE_MULTIPLAYER_RULE_SETTINGS)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void MultiplayerRuleSettingsScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<NetworkSystem>());
}

void MultiplayerRuleSettingsScene::initEntities()
{
    
}
