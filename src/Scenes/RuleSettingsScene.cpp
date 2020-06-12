/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsScene
*/

#include "Scenes/RuleSettingsScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;

RuleSettingsScene::RuleSettingsScene() : AScene(Scenes::SCENE_RULE_SETTINGS)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void RuleSettingsScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextureSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
}

is::components::RulesComponent &RuleSettingsScene::getRulesComponent() const
{
    auto entities = AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<is::components::RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}

void RuleSettingsScene::initEntities()
{
    is::components::RulesComponent &rules = getRulesComponent();

    initEntity(is::prefabs::RuleSettingsPrefabs::createBackground());
    initEntity(is::prefabs::RuleSettingsPrefabs::createReturnButton());
    initEntity(is::prefabs::RuleSettingsPrefabs::createRuleSettings(), false);

    is::components::RulesSettingComponent &rulesSetting =
        *static_cast<is::components::RulesSettingComponent *>(_componentManager->getComponentsByType(typeid(is::components::RulesSettingComponent).hash_code())[0].get());

    initEntity(is::prefabs::RuleSettingsPrefabs::createSettingsBackground(rulesSetting));
    initEntity(is::prefabs::RuleSettingsPrefabs::createNumberOfPlayersRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createIconsRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createMaxTimeRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createSeedRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createPowerupFrequency(rulesSetting, rules));
}
