/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#include "Scenes/GameScene.hpp"
#include "MapLoader.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;
using namespace is::prefabs;

bool GameScene::loadMap = false;

GameScene::GameScene() :
AScene(Scenes::SCENE_GAME)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void GameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::KeyboardInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::PauseSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CharacterControllerSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::LightSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JumpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::GravitySystem>());
    _systemManager->addSystem(std::make_shared<is::systems::MovementSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::BombSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::FireSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::SliderSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::PowerUpSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel1System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel2System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel3System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel4System>());
    _systemManager->addSystem(std::make_shared<is::systems::AIControllerLevel5System>());
    _systemManager->addSystem(std::make_shared<is::systems::ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::JoystickCursorSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::EndGameSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AlertSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextureSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TimerSystem>());
}

void GameScene::initEntities()
{
    auto &characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    //std::cout << " size : " << characters.size() << std::endl;
    auto &rules = getRulesComponent();
    MapGenerator mg;
    std::vector<std::shared_ptr<is::ecs::Component>> a;

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    std::cout << "Seed :" << rules.getSeed() << std::endl;
    if (!loadMap)
        mg.generateMap(*this, rules.getSeed(), 15, 13, a);
    else {
        std::vector<std::vector<int>> tmpMap = MapLoader::loadMap("./testmap");
        mg.createMap(*this, tmpMap, MapLoader::x / 2, MapLoader::y / 2, a);
    }

    if (!loadMap) {
    for (int i = 0; i < rules.getNumberOfPlayers() && i != 4; i++) {
        auto &ch = *static_cast<CharacterComponent *>(characters[i].get());
    
        switch (i)
        {
        case 0:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(-5 * 3, 0, 6 * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                rules.getAiLevels()[0]
            ));
            break;
        case 1:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(5 * 3, 0, -6 * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                rules.getAiLevels()[1]
            ));
            break;
        case 2:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(-5 * 3, 0, -6 * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                rules.getAiLevels()[2]
            ));
            break;
        case 3:
            initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(5 * 3, 0, 6 * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                rules.getAiLevels()[3]
            ));
            break;
        default:
            break;
        }
    }
    } else {
        for (size_t i = 0; i < MapLoader::playerNumber; i++) {
            std::cout << i << std::endl;
        auto &ch = *static_cast<CharacterComponent *>(characters[i].get());
        ch.characterType = MapLoader::charactersInfo[i].type;
        ch.presetNumber = MapLoader::charactersInfo[i].preset; 
            initEntity(GlobalPrefabs::createBombermanCharacter(
                MapLoader::charactersInfo[i].position,
                ch,
                *_componentManager.get(),
                ch.texturePath,
                MapLoader::charactersInfo[i].level
            ));
        }
        for (size_t i = 0; i < MapLoader::bonusNumber; i++) {
            std::cout << i << std::endl;
            switch (MapLoader::bonusInfo[i].type) {
                case (0):
                    initEntity(GlobalPrefabs::createBombUpPowerUp(MapLoader::bonusInfo[i].position));
                case (1):
                    initEntity(GlobalPrefabs::createFireUpPowerUp(MapLoader::bonusInfo[i].position));
                case (2):
                    initEntity(GlobalPrefabs::createSpeedUpPowerUp(MapLoader::bonusInfo[i].position));
                default:
                    initEntity(GlobalPrefabs::createWallPassPowerUp(MapLoader::bonusInfo[i].position));
            }
        }
    }

    initEntity(GlobalPrefabs::createTimer(rules));
    MapLoader::componentManager = _componentManager;
}

RulesComponent &GameScene::getRulesComponent() const
{
    auto entities = AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<RulesComponent>();

        if (rules.has_value())
            return (*rules.value());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}
