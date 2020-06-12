/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#include "Scenes/MultiplayerGameScene.hpp"

using namespace is::systems;
using namespace is::scenes;
using namespace is::ecs;
using namespace is::prefabs;

MultiplayerGameScene::MultiplayerGameScene() :
AScene(Scenes::SCENE_PRESETSELECTION)
{
    _entityManager = std::make_shared<EntityManager>();
    _componentManager = std::make_shared<ComponentManager>();
    _systemManager = std::make_shared<SystemManager>(_componentManager, _entityManager);
}

void MultiplayerGameScene::initSystems()
{
    _systemManager->addSystem(std::make_shared<TimeSystem>());
    _systemManager->addSystem(std::make_shared<WindowSystem>());
    _systemManager->addSystem(std::make_shared<CameraSystem>());
    _systemManager->addSystem(std::make_shared<ModelRendererSystem>());
    _systemManager->addSystem(std::make_shared<KeyboardInputSystem>());
    _systemManager->addSystem(std::make_shared<JoystickInputSystem>());
    _systemManager->addSystem(std::make_shared<CharacterControllerSystem>());
    _systemManager->addSystem(std::make_shared<LightSystem>());
    _systemManager->addSystem(std::make_shared<MovementSystem>());
    _systemManager->addSystem(std::make_shared<BombSystem>());
    _systemManager->addSystem(std::make_shared<FireSystem>());
    _systemManager->addSystem(std::make_shared<ButtonSystem>());
    _systemManager->addSystem(std::make_shared<TextSystem>());
    _systemManager->addSystem(std::make_shared<SliderSystem>());
    _systemManager->addSystem(std::make_shared<ImageSystem>());
    _systemManager->addSystem(std::make_shared<PowerUpSystem>());
    _systemManager->addSystem(std::make_shared<AIControllerLevel2System>());
    _systemManager->addSystem(std::make_shared<ParticuleSystem>());
    _systemManager->addSystem(std::make_shared<CursorSystem>());
    _systemManager->addSystem(std::make_shared<NetworkSystem>());
    _systemManager->addSystem(std::make_shared<NetworkInputSystem>());
    _systemManager->addSystem(std::make_shared<AlertSystem>());
    _systemManager->addSystem(std::make_shared<HudSystem>());
    _systemManager->addSystem(std::make_shared<EndGameSystem>());
    _systemManager->addSystem(std::make_shared<TimerSystem>());
    _systemManager->addSystem(std::make_shared<AudioSystem>());
}

void MultiplayerGameScene::initEntities()
{
    int x = 0;
    int y = 0;
    std::shared_ptr<is::ecs::Entity> e;
    auto characters = _componentManager->getComponentsByType(typeid(CharacterComponent).hash_code());
    MapGenerator mg;
    auto &rules = getRulesComponent();

    if (characters.size() != 4)
        throw is::exceptions::Exception("GameScene", "Error with character components");
    mg.generateMap(*this, rules.getSeed(), 15, 13, _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code()));
    initEntity(GlobalPrefabs::createTimer(rules));
    for (int i = 0; i != rules.getNumberOfPlayers(); i++) {
        auto &ch = *static_cast<CharacterComponent *>(characters[i].get());
        x = (i % 2 ? 5 : -5);
        y = (i == 1 || i == 2 ? -6 : 6);
        e = initEntity(GlobalPrefabs::createBombermanCharacter(
                irr::core::vector3df(x * 3, 0, y * 3),
                ch,
                *_componentManager.get(),
                ch.texturePath,
                2
        ));
        initEntity(GlobalPrefabs::createPlayerHud(
            *static_cast<BombermanComponent *>(e->getComponent<BombermanComponent>()->get()),
            ch.texturePath,
            i
        ));
    }
}

void MultiplayerGameScene::awake()
{
    AScene::awake();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.addEventKeyReleased(irr::EKEY_CODE::KEY_KEY_P, []() {
            if (is::Game::getCurrentScene() == SCENE_GAME)
                is::Game::setActualScene(SCENE_PAUSE);
            else if (is::Game::getCurrentScene() == SCENE_PAUSE)
                is::Game::setActualScene(SCENE_GAME);
        });
    }
}

void MultiplayerGameScene::onTearDown()
{
    AScene::onTearDown();
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        WindowComponent &window = *static_cast<WindowComponent *>(elem.get());
        window.eventManager.removeEventKeyReleased(irr::EKEY_CODE::KEY_KEY_P);
    }
}

is::components::RulesComponent &MultiplayerGameScene::getRulesComponent() const
{ 
    auto entities = AScene::_entitySaver->getEntities();

    for (const auto &entity : entities) {
        auto rules = entity->getComponent<is::components::RulesComponent>();

        if (rules.has_value())
            return (*rules.value().get());
    }
    throw is::exceptions::ECSException("Could not found Rules component");
}