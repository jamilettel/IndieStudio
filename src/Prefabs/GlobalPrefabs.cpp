/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"
#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::components;

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<TimeComponent>(e);
    e->addComponent<AudioComponent>(e, RESSOURCE("lol.wav"), MUSIC, false);
    e->addComponent<WindowComponent>(e, "Indie Studio");
    e->addComponent<LightComponent>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0));
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("cubb.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGrassBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("grass.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::BRKBL_BLK);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("crate.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createBomb(irr::core::vector3df position,
    int range,
    std::shared_ptr<is::components::BombermanComponent> &bm)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::BOMB);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("bomb.obj"), "Indie Studio");
    e->addComponent<BombComponent>(e, bm, 3, range);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createBombUpPowerUp(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 2, 2));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Lollipop.obj"), "Indie Studio");
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::BOMB_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::PLAYER);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createSpeedUpPowerUp(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 2, 2));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Star.obj"), "Indie Studio");
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::SPEED_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::PLAYER);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createFireUpPowerUp(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 2, 2));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Mushroom_1.obj"), "Indie Studio");
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::FIRE_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::PLAYER);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallPassPowerUp(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 2, 2));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Mushroom_2.obj"), "Indie Studio");
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::WALL_PASS);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::PLAYER);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createFire(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::FIRE);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Block_Pause.obj"), "Indie Studio");
    e->addComponent<FireComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::GROUND);
    collider.addCollisionWithLayer(is::ecs::Entity::BOMB);
    collider.addCollisionWithLayer(is::ecs::Entity::FIRE);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createPlayer(irr::core::vector3df pos)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::PLAYER);

    TransformComponent &transform = e->addComponent<TransformComponent>(
        e,
        pos,
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(3.5, 3.5, 3.5)
        );
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(2, 2, 2)
    );
    MovementComponent &movement = e->addComponent<MovementComponent>(
        e,
        transform,
        collider
    );
    AudioComponent &audio = e->addComponent<is::components::AudioComponent>(
        e,
        RESSOURCE("footstep.wav"),
        is::components::SOUND
    );
    e->addComponent<CharacterControllerComponent>(
        e,
        transform,
        movement,
        audio,
        "Indie Studio",
        0.1
    );
    collider.addCollisionWithLayer(is::ecs::Entity::GROUND);
    collider.addCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    e->addComponent<GravityComponent>(e, movement);
    transform.position.Y = 10;
    e->addComponent<BombermanComponent>(e);
    e->addComponent<JumpComponent>(e, movement);
    InputManagerComponent &input = e->addComponent<InputManagerComponent>(e);
    KeyboardInputComponent &keyboard = e->addComponent<KeyboardInputComponent>(e, input);
    keyboard.bind(irr::KEY_KEY_W, "MoveVerticalAxis", 1);
    keyboard.bind(irr::KEY_KEY_S, "MoveVerticalAxis", -1);
    keyboard.bind(irr::KEY_KEY_D, "MoveHorizontalAxis", -1);
    keyboard.bind(irr::KEY_KEY_A, "MoveHorizontalAxis", 1);
    keyboard.bind(irr::KEY_KEY_E, "DropBomb", 1);
    keyboard.bind(irr::KEY_SPACE, "Jump", 1);
    JoystickInputComponent &joystick = e->addComponent<JoystickInputComponent>(e, input);
    joystick.bindAxis(1, "MoveVerticalAxis", -1, 1);
    joystick.bindAxis(0, "MoveHorizontalAxis", -1, 1);
    joystick.bindButton(2, "DropBomb", 1);
    joystick.bindButton(0, "Jump", 1);
    joystick.assignJoystick(0);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createAI(irr::core::vector3df pos)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::PLAYER);

    TransformComponent &transform = e->addComponent<TransformComponent>(
        e,
        pos,
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(3.5, 3.5, 3.5)
        );
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(2, 2, 2)
    );
    MovementComponent &movement = e->addComponent<MovementComponent>(
        e,
        transform,
        collider
    );
    AudioComponent &audio = e->addComponent<is::components::AudioComponent>(
        e,
        RESSOURCE("footstep.wav"),
        is::components::SOUND
    );
    e->addComponent<CharacterControllerComponent>(
        e,
        transform,
        movement,
        audio,
        "Indie Studio",
        0.1
    );
    collider.addCollisionWithLayer(is::ecs::Entity::GROUND);
    collider.addCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    e->addComponent<GravityComponent>(e, movement);
    transform.position.Y = 10;
    e->addComponent<BombermanComponent>(e);
    e->addComponent<JumpComponent>(e, movement);
    InputManagerComponent &input = e->addComponent<InputManagerComponent>(e);
    e->addComponent<AIControllerComponent>(e, input);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createCanvas()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "TEST",
        "Indie Studio",
        10, 10, 100, 100,
        [](){
            std::cout << "test" << std::endl;
        }
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Test Text",
        "Indie Studio",
        100, 10, 200, 200,
        false
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("test.png"),
        "Indie Studio",
        500, 10, true
    );
    e->addComponent<is::components::SliderComponent>(
        e,
        "",
        "Indie Studio",
        0, 10, 20,
        1000, 10, 500, 100
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createSplashScreen()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("background.png"),
        "Indie Studio",
        0, 0, true
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createMainMenu()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
        "Indie Studio",
        0, 0, true
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/logo.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 541 / 2, 50, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2,
        is::components::WindowComponent::_height / 2.5 + 50,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_GAME);
        },
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2,
        is::components::WindowComponent::_height / 2.5 + 200,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        RESSOURCE("ui/main_menu/button_quit.png"),
        RESSOURCE("ui/main_menu/button_quit_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width - 80,
        is::components::WindowComponent::_height - 150,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/Controllers_BTN.png"),
        RESSOURCE("ui/main_menu/Controllers_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width - 80,
        is::components::WindowComponent::_height - 70,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/Settings_BTN.png"),
        RESSOURCE("ui/main_menu/Settings_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 50 / 2,
        is::components::WindowComponent::_height - 100,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/Scores_BTN.png"),
        RESSOURCE("ui/main_menu/Scores_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        is::components::WindowComponent::_height - 150,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/FAQ_BTN.png"),
        RESSOURCE("ui/main_menu/FAQ_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        is::components::WindowComponent::_height - 150,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/FAQ_BTN.png"),
        RESSOURCE("ui/main_menu/FAQ_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        is::components::WindowComponent::_height - 70,
        50, 50,
        [](){
        },
        RESSOURCE("ui/main_menu/Info_BTN.png"),
        RESSOURCE("ui/main_menu/Info_BTN_pressed.png")
    );
    return (e);
}
