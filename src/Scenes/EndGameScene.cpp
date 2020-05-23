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

    std::for_each(entities.begin(), entities.end(), [](std::shared_ptr<is::ecs::Entity> &e) {
        auto c = e->getComponent<CharacterComponent>();

        if (!c.has_value())
            return;
        std::cout << "Bomb posed : " << c.value()->getNbBombPosed() << std::endl;
    });
    initEntity(prefabs::EndGamePrefabs::createBackground(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer2(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer3(), false);
    initEntity(prefabs::EndGamePrefabs::createPlayer4(), false);
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
    if (changeScene)
        is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
}