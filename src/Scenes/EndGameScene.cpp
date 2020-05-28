/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndEndGameScene
*/

#include "Scenes/EndGameScene.hpp"

using namespace is::components;

is::scenes::EndGameScene::EndGameScene() :
AScene(is::ecs::Scenes::SCENE_ENDGAME)
{
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
}

void is::scenes::EndGameScene::initSystems()
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

void is::scenes::EndGameScene::initEntities()
{
    auto entities = is::ecs::AScene::_entitySaver->getEntities();

    initEntity(prefabs::EndGamePrefabs::createBackground(), false);
    int i = 0;
    std::for_each(entities.begin(), entities.end(), [this, &i, &entities](std::shared_ptr<is::ecs::Entity> &e) {
        auto components = e->getComponentsOfType<CharacterComponent>();

        std::for_each(components.begin(), components.end(), [&i, this](std::weak_ptr<Component> &component) {
            std::vector<std::pair<std::string, std::string>> infos;
            auto &c = *static_cast<CharacterComponent *>(component.lock().get());

            infos.emplace_back(std::make_pair("Bombs laid", std::to_string(c.getNbBombPosed())));
            infos.emplace_back(std::make_pair("Bonus collected", std::to_string(c.getNbBonueCollected())));
            infos.emplace_back(std::make_pair("Players killed", std::to_string(c.getNbCharactersKilled())));
            infos.emplace_back(std::make_pair("Time playing", std::to_string(c.getTimePlaying())));
            switch (i)
            {
            case 0:
                initEntity(prefabs::EndGamePrefabs::createPlayer(infos, c.isAI(), c.texturePath), false);
                break;
            case 1:
                initEntity(prefabs::EndGamePrefabs::createPlayer2(infos, c.isAI(), c.texturePath), false);
                break;
            case 2:
                initEntity(prefabs::EndGamePrefabs::createPlayer3(infos, c.isAI(), c.texturePath), false);
                break;
            case 3:
                initEntity(prefabs::EndGamePrefabs::createPlayer4(infos, c.isAI(), c.texturePath), false);
                break;
            default:
                break;
            }
            i++;
        });
    });
    // std::remove_if(entities.begin(), entities.end(), [](std::shared_ptr<is::ecs::Entity> &e) -> bool {
    //     return (e->getComponent<CharacterComponent>().has_value());
    // });
}

void is::scenes::EndGameScene::update()
{
    AScene::update();
    std::vector<std::shared_ptr<Component>> &statsComponents = _componentManager->getComponentsByType(typeid(StatsComponent).hash_code());
    bool changeScene = true;

    std::for_each(statsComponents.begin(), statsComponents.end(), [&changeScene](std::shared_ptr<Component> &component) {
        StatsComponent &stats = *static_cast<StatsComponent *>(component.get());

        if (!stats.isContinue())
            changeScene = false;
    });
    if (changeScene) {
        is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
        is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
    }
}