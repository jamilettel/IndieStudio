/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"
#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif
#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::components;
using namespace is::ecs;
using namespace is::prefabs;

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createJoystickCursor(int joystickId, std::shared_ptr<WindowComponent> &window)
{
    auto e = std::make_shared<Entity>();

    auto &cursorJoystick = e->addComponent<ImageComponent>(
        e,
        RESSOURCE("/ui/cursor/cursor.png"),
        "Indie Studio",
        0,
        0);
    cursorJoystick.layer = 10;
    cursorJoystick.init(window);

    auto &inputManager = e->addComponent<InputManagerComponent>(e);
    inputManager.setValue("Horizontal", 0);
    inputManager.setValue("Vertical", 0);
    inputManager.setValue("Click", 0);

    auto &joystickInput = e->addComponent<JoystickInputComponent>(e, inputManager);
    joystickInput.assignJoystick(joystickId);
    joystickInput.bindAxis(0, "Horizontal", 1, -1);
    joystickInput.bindAxis(1, "Vertical", 1, -1);
    joystickInput.bindButton(0, "Click", 1);

    auto &cursor = e->addComponent<CursorComponent>(e, cursorJoystick, *window.get(), false);
    e->addComponent<JoystickCursorComponent>(e, cursor, joystickInput);

    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<TimeComponent>(e);
    e->addComponent<AudioComponent>(e, RESSOURCE("lol.wav"), MUSIC, false);
    auto &window = e->addComponent<WindowComponent>(e, "Indie Studio");
    auto &cursor = e->addComponent<ImageComponent>(e, RESSOURCE("/ui/cursor/cursor.png"), "Indie Studio", 0, 0);
    cursor.layer = 10;
    e->addComponent<CursorComponent>(e, cursor, window);
    e->addComponent<LightComponent>(e, "Indie Studio", core::vector3df(20, 500, -20), video::SColorf(2.5f, 2.3f, 1.9f, 1.0f), 750.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0), true);

    // for (size_t i = 0; i < window.joysticks.size(); i++) {
    //     auto &cursorJoystick = e->addComponent<ImageComponent>(
    //         e,
    //         RESSOURCE("/ui/cursor/cursor.png"),
    //         "Indie Studio",
    //         0,
    //         0);
    //     cursorJoystick.layer = 10;
    //     auto &cursor = e->addComponent<CursorComponent>(e, cursorJoystick, window, false);
    //     e->addComponent<JoystickCursorComponent>(
    //         e,
    //         cursor,
    //         window.joysticks[i].Joystick
    //         );

    // }

    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createGlobalPrefabMultiplayer()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<NetworkComponent>(e);
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createSplashScreen()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/splashscreen.png"),
        "Indie Studio",
        0, 0, true
    ).layer = 9999;
    return (e);
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createMainMenu()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/logo.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2, 50, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 50,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    // MULTIPLAYER TEMP
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 300,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MULTIPLAYER_HUB);
        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 200,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        true,
        RESSOURCE("ui/main_menu/button_quit.png"),
        RESSOURCE("ui/main_menu/button_quit_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_CONTROLLERS);
        },
        true,
        RESSOURCE("ui/main_menu/Controllers_BTN.png"),
        RESSOURCE("ui/main_menu/Controllers_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_SETTINGS);
        },
        true,
        RESSOURCE("ui/main_menu/Settings_BTN.png"),
        RESSOURCE("ui/main_menu/Settings_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 50 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 100,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_RECORD);
        },
        true,
        RESSOURCE("ui/main_menu/Scores_BTN.png"),
        RESSOURCE("ui/main_menu/Scores_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_HOWTOPLAY);
        },
        true,
        RESSOURCE("ui/main_menu/FAQ_BTN.png"),
        RESSOURCE("ui/main_menu/FAQ_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_CREDIT);
        },
        true,
        RESSOURCE("ui/main_menu/Info_BTN.png"),
        RESSOURCE("ui/main_menu/Info_BTN_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createPause()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/Pause/Pause.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 300 / 2, 300, true
    ).layer = 1;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/Pause/logo.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2, 30, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 100,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_GAME);
        },
        true,
        RESSOURCE("ui/Pause/Continue_BTN.png"),
        RESSOURCE("ui/Pause/Continue_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 250,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        true,
        RESSOURCE("ui/Pause/button_quit.png"),
        RESSOURCE("ui/Pause/button_quit_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_SETTINGS);
        },
        true,
        RESSOURCE("ui/Pause/Settings_BTN.png"),
        RESSOURCE("ui/Pause/Settings_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 50 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 100,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_RECORD);
        },
        true,
        RESSOURCE("ui/Pause/Scores_BTN.png"),
        RESSOURCE("ui/Pause/Scores_BTN_pressed.png")
    ).layer = 2;
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createCredit()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/Credits/Information.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 606 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Credits/Return_BTN.png"),
        RESSOURCE("ui/Credits/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<TextComponent>(
        e,
        "Epitech Project Tek2",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 150,
        350, 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 68, 68, 68)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Amaury Lecomte",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 280,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Benjamin Bourgeois",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 380,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Jamil Ettel",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 480,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Louis Deschanel",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 580,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Nathan Quentel",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 680,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<TextComponent>(
        e,
        "Tristan Bouillot",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 780,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createHowToPlay()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/HowToPlay/Header.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 700 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/HowToPlay/Return_BTN.png"),
        RESSOURCE("ui/HowToPlay/Return_BTN_pressed.png")
    ).layer = 2;
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createRecord()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/Record/Record.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 280 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Record/Return_BTN.png"),
        RESSOURCE("ui/Record/Return_BTN_pressed.png")
    ).layer = 2;
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createMultiplayerHub(std::shared_ptr<is::components::NetworkComponent> nc)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        RESSOURCE("ui/Record/Record.png"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 280 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Record/Return_BTN.png"),
        RESSOURCE("ui/Record/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 300,
        350, 100,
        [nc](){
            nc->writeQueue.push("create lobby\n");
        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 50,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY_CHOICE);
        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createMultiplayerLobbyChoice(std::shared_ptr<is::components::NetworkComponent> nc)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Record/Record.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 280 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Record/Return_BTN.png"),
        RESSOURCE("ui/Record/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 50,
        350, 100,
        [nc](){
            nc->writeQueue.push("join lobby 0\n");
        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createMultiplayerLobby(std::shared_ptr<is::components::NetworkComponent> nc)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Record/Record.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 280 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Record/Return_BTN.png"),
        RESSOURCE("ui/Record/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 500,
        350, 100,
        [nc](){
            nc->writeQueue.push("start game\n");

        },
        true,
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    return e;
}
