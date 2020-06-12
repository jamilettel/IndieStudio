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
    _systemManager->addSystem(std::make_shared<is::systems::HudSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::AudioSystem>());
}

void GameScene::initEntities()
{
    int x = 0;
    int y = 0;
    std::shared_ptr<is::ecs::Entity> e;
    auto &characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    //std::cout << " size : " << characters.size() << std::endl;
    auto &rules = getRulesComponent();
    MapGenerator mg;
    std::vector<std::shared_ptr<is::ecs::Component>> a;
    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    if (loadMap) {
        std::vector<std::vector<int>> tmpMap = MapLoader::loadMap("./testmap");
        mg.createMap(*this, tmpMap, MapLoader::x / 2, MapLoader::y / 2, a);
    }

    if (!loadMap) {
        mg.generateMap(*this, rules.getSeed(), 15, 13, a);
    for (int i = 0; i < rules.getNumberOfPlayers() && i != 4; i++) {
        auto &ch = *static_cast<CharacterComponent *>(characters[i].get());
        x = (i % 2 ? 5 : -5);
        y = (i == 1 || i == 2 ? -6 : 6);
        e = initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(x * 3, 0, y * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                rules.getAiLevels()[i]
        ));
        initEntity(GlobalPrefabs::createPlayerHud(
            *static_cast<BombermanComponent *>(e->getComponent<BombermanComponent>()->get()),
            ch.texturePath,
            i
        ));
    }
    } else {
        for (size_t i = 0; i < MapLoader::playerNumber; i++) {
            std::cout << i << std::endl;
            auto &ch = *static_cast<CharacterComponent *>(characters[i].get());
            ch.characterType = MapLoader::charactersInfo[i].type;
            ch.presetNumber = MapLoader::charactersInfo[i].preset;
            std::cout << "time : ";
            std::cout << MapLoader::charactersInfo[i].time << std::endl;
            initEntity(GlobalPrefabs::createBombermanCharacter(
                MapLoader::charactersInfo[i].position,
                ch,
                *_componentManager.get(),
                ch.texturePath,
                MapLoader::charactersInfo[i].level,
                MapLoader::charactersInfo[i].alive
            ));
            auto &tmp = _componentManager->getComponentsByType(typeid(is::components::BombermanComponent).hash_code());
            auto &bm = *static_cast<BombermanComponent *>(tmp[i].get());
            bm.bombRange = MapLoader::charactersInfo[i].bombRange;
            bm.bombNumber = MapLoader::charactersInfo[i].bombNumber;
            bm.speedCount = MapLoader::charactersInfo[i].speedUp;
            bm.speedMult = MapLoader::charactersInfo[i].speedMult;
            bm.wallPass = MapLoader::charactersInfo[i].wallPass;
            ch.setNbBombPosed(MapLoader::charactersInfo[i].bombPosed);
            ch.setNbBonusCollected(MapLoader::charactersInfo[i].bonusCollected);
            ch.setNbCharactersKilled(MapLoader::charactersInfo[i].kills);
            ch.setTimePlaying(MapLoader::charactersInfo[i].time);
            if (bm.wallPass)    
                bm.getEntity()->getComponent<is::components::ColliderComponent>()->get()->removeCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
            initEntity(GlobalPrefabs::createPlayerHud(
                bm,
                ch.texturePath,
                i
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
    if (loadMap) {
        auto &tmpRule = _componentManager->getComponentsByType(typeid(TimerComponent).hash_code())[0];
        auto &tmpTime = *static_cast<TimerComponent *>(tmpRule.get());
        tmpTime.setTime(MapLoader::timer);
    }
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
