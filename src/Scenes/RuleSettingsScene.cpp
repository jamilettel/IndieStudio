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
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<TextureSystem>());
    _systemManager->addSystem(std::make_shared<ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
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

    is::components::RulesSettingComponent &rulesSetting = *static_cast<is::components::RulesSettingComponent *>(_componentManager->getComponentsByType(typeid(is::components::RulesSettingComponent).hash_code())[0].get());

    initEntity(is::prefabs::RuleSettingsPrefabs::createSettingsBackground(rulesSetting));
    initEntity(is::prefabs::RuleSettingsPrefabs::createNumberOfPlayersRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createIconsRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createMaxTimeRule(rulesSetting, rules));
    initEntity(is::prefabs::RuleSettingsPrefabs::createModeFpsRule(rulesSetting, rules));
}
