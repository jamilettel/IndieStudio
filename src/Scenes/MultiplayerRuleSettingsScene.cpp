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
using namespace is::prefabs;
using namespace is::exceptions;

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
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<TextureSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<NetworkSystem>());
}

RulesComponent &MultiplayerRuleSettingsScene::getRulesComponent() const
{
    auto entities = AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw ECSException("Could not found Rules component");
}

void MultiplayerRuleSettingsScene::initEntities()
{
    RulesComponent &rules = getRulesComponent();

    auto e = _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())[0];
    const auto &ptr = std::static_pointer_cast<is::components::NetworkComponent>(e);

    initEntity(RuleSettingsPrefabs::createBackground());
    initEntity(RuleSettingsPrefabs::createOkButton(ptr, rules));
    initEntity(RuleSettingsPrefabs::createReturnButton());
    initEntity(RuleSettingsPrefabs::createRuleSettings(), false);

    RulesSettingComponent &rulesSetting =
        *static_cast<RulesSettingComponent *>(_componentManager->getComponentsByType(typeid(RulesSettingComponent).hash_code())[0].get());

    initEntity(RuleSettingsPrefabs::createSettingsBackground(rulesSetting));
    initEntity(RuleSettingsPrefabs::createNumberOfPlayersRule(rulesSetting, rules));
    initEntity(RuleSettingsPrefabs::createIconsRule(rulesSetting, rules));
    initEntity(RuleSettingsPrefabs::createMaxTimeRule(rulesSetting, rules));
    initEntity(RuleSettingsPrefabs::createSeedRule(rulesSetting, rules));
}
