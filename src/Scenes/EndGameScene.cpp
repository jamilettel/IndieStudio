/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndEndGameScene
*/

#include "Scenes/EndGameScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;
using namespace is::components;

EndGameScene::EndGameScene() :
AScene(Scenes::SCENE_ENDGAME)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void EndGameScene::initSystems()
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
    _systemManager->addSystem(std::make_shared<JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
}

void EndGameScene::initEntities()
{
    auto entities = is::ecs::AScene::_entitySaver->getEntities();
    auto &rules = getRulesComponent();
    auto &characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());

    std::vector<int> windowPos = initWindowPosForPlayer(rules.getNumberOfPlayers());
    std::vector<std::pair<float, float>> posModelPlayer = initPosModelPlayer(rules.getNumberOfPlayers());

    initEntity(prefabs::EndGamePrefabs::createBackground(), false);

    for (int i = 0; i < rules.getNumberOfPlayers(); i++) {
        auto &c = *std::static_pointer_cast<CharacterComponent>(characters[i]);
        std::vector<std::pair<std::string, std::string>> infos;

        infos.emplace_back(std::make_pair("Bombs laid", std::to_string(c.getNbBombPosed())));
        infos.emplace_back(std::make_pair("Bonus collected", std::to_string(c.getNbBonusCollected())));
        infos.emplace_back(std::make_pair("Players killed", std::to_string(c.getNbCharactersKilled())));
        infos.emplace_back(std::make_pair("Time playing", c.getTimeString()));

        switch (i)
        {
        case 0:
            initEntity(prefabs::EndGamePrefabs::createPlayer(infos,
                                                             c.characterType == c.MULTIPLAYER_PLAYER || c.isAI(),
                                                             c.texturePath,
                                                             windowPos[i],
                                                             posModelPlayer[i],
                                                             c.getPosition()),
                                                             false);
            break;
        case 1:
            initEntity(prefabs::EndGamePrefabs::createPlayer(infos,
                                                             c.characterType == c.MULTIPLAYER_PLAYER || c.isAI(),
                                                             c.texturePath,
                                                             windowPos[i],
                                                             posModelPlayer[i],
                                                             c.getPosition()),
                                                             false);
            break;
        case 2:
            initEntity(prefabs::EndGamePrefabs::createPlayer(infos,
                                                             c.characterType == c.MULTIPLAYER_PLAYER || c.isAI(),
                                                             c.texturePath,
                                                             windowPos[i],
                                                             posModelPlayer[i],
                                                             c.getPosition()),
                                                             false);
            break;
        case 3:
            initEntity(prefabs::EndGamePrefabs::createPlayer(infos,
                                                             c.characterType == c.MULTIPLAYER_PLAYER || c.isAI(),
                                                             c.texturePath,
                                                             windowPos[i],
                                                             posModelPlayer[i],
                                                             c.getPosition()),
                                                             false);
            break;
        default:
            break;
        }
    }
}

void EndGameScene::update()
{
    AScene::update();
    std::vector<std::shared_ptr<Component>> &statsComponents = _componentManager->getComponentsByType(typeid(is::components::StatsComponent).hash_code());
    bool changeScene = true;

    std::for_each(statsComponents.begin(), statsComponents.end(), [&changeScene](std::shared_ptr<Component> &component) {
        is::components::StatsComponent &stats = *static_cast<is::components::StatsComponent *>(component.get());

        if (!stats.isContinue())
            changeScene = false;
    });
    if (changeScene) {
        is::Game::setActualScene(SCENE_MAIN_MENU);
        is::Game::setActualScene(SCENE_PRESETSELECTION);
    }
}

is::components::RulesComponent &EndGameScene::getRulesComponent() const
{
    auto entities = is::ecs::AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}

std::vector<int> EndGameScene::initWindowPosForPlayer(int nbPlayers) const
{
    std::vector<int> value;

    if (nbPlayers == 4) {
        value.emplace_back(2.5);
        value.emplace_back(26.3);
        value.emplace_back(51.3);
        value.emplace_back(76.3);
    } else if (nbPlayers == 3) {
        value.emplace_back(10);
        value.emplace_back(40);
        value.emplace_back(70);
    } else if (nbPlayers == 2) {
        value.emplace_back(20);
        value.emplace_back(60);
    }
    return (value);
}

std::vector<std::pair<float, float>> EndGameScene::initPosModelPlayer(int nbPlayers) const
{
    std::vector<std::pair<float, float>> value;

    if (nbPlayers == 4) {
        value.emplace_back(std::make_pair(19, -120));
        value.emplace_back(std::make_pair(6.5, -100));
        value.emplace_back(std::make_pair(-6, -70));
        value.emplace_back(std::make_pair(-19, -50));
    } else if (nbPlayers == 3) {
        value.emplace_back(std::make_pair(15, -110));
        value.emplace_back(std::make_pair(-0.5, -85));
        value.emplace_back(std::make_pair(-16, -60));
    } else if (nbPlayers == 2) {
        value.emplace_back(std::make_pair(10, -110));
        value.emplace_back(std::make_pair(-11, -60));
    }
    return value;
}
