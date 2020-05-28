/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsScene
*/

#include "Scenes/RuleSettingsScene.hpp"

using namespace is::ecs;
using namespace is::scenes;
using namespace is::components;

RuleSettingsScene::RuleSettingsScene() : AScene(is::ecs::Scenes::SCENE_RULE_SETTINGS)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void RuleSettingsScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextureSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
}

RulesComponent &RuleSettingsScene::getRulesComponent() const
{
    auto entities = is::ecs::AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}

void RuleSettingsScene::initEntities()
{
    RulesComponent &rules = getRulesComponent();

    initEntity(is::prefabs::RuleSettingsPrefabs::createBackground());
    initEntity(is::prefabs::RuleSettingsPrefabs::createSaveButton());
    initEntity(is::prefabs::RuleSettingsPrefabs::createReturnButton());
    initEntity(is::prefabs::RuleSettingsPrefabs::createRuleSettings(), false);

    RulesSettingComponent &rulesSetting = *static_cast<RulesSettingComponent *>(_componentManager->getComponentsByType(typeid(RulesSettingComponent).hash_code())[0].get());

    initEntity(is::prefabs::RuleSettingsPrefabs::createSettingsBackground(rulesSetting));
    initEntity(is::prefabs::RuleSettingsPrefabs::createNumberOfPlayersRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createIconsRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createMaxTimeRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createModeFpsRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createEmptyRule(rulesSetting, rules));
}
