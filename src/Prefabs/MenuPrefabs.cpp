/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Menu Prefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"
#include "MapLoader.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#ifdef _WIN32
#define F_OK 00
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::ecs;
using namespace is::prefabs;
using namespace is::components;

std::shared_ptr<Entity> GlobalPrefabs::createJoystickCursor(int joystickId, const std::shared_ptr<WindowComponent> &window, int cursorNb)
{
    auto e = std::make_shared<Entity>();
    std::string cursorImage = "ui/cursor/cursor" + std::to_string(cursorNb) + ".png";

    auto &cursorJoystick = e->addComponent<ImageComponent>(
        e,
        cursorImage,
        "Indie Studio",
        0,
        0);
    cursorJoystick.layer = 9;

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

std::shared_ptr<Entity> GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<TimeComponent>(e);
    auto &window = e->addComponent<WindowComponent>(e, "Indie Studio", irr::core::dimension2d<irr::u32>(1920, 1080), true);
    auto &cursor = e->addComponent<ImageComponent>(e, "ui/cursor/cursor.png", "Indie Studio", 0, 0);
    cursor.layer = 10;
    e->addComponent<CursorComponent>(e, cursor, window);
    e->addComponent<LightComponent>(e, "Indie Studio", irr::core::vector3df(20, 500, -20), irr::video::SColorf(2.5f, 2.3f, 1.9f, 1.0f), 750.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", irr::core::vector3df(-15, 27, 0), irr::core::vector3df(-3, 0, 0), true);
    e->addComponent<AlertComponent>(e);
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createGlobalPrefabMultiplayer()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<NetworkComponent>(e);
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createSplashScreen()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/splashscreen.png",
        "Indie Studio",
        0, 0, true
    ).layer = 9999;
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createMainMenu()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        "ui/main_menu/logo.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2,
        50,
        true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 8 / 20,
        350, 100,
        [](){
            is::Game::setActualScene(SCENE_PRESETSELECTION);
        },
        true,
        "ui/main_menu/button_play.png",
        "ui/main_menu/button_play_pressed.png"
    );
     e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 11 / 20,
        350, 100,
        [](){
            if (access(RESSOURCE(".savemap").c_str(), F_OK) == -1)
                return;
            is::scenes::GameScene::loadMap = true;
            is::Game::setActualScene(SCENE_GAME);
        },
        true,
        "ui/Save/Load_BTN.png",
        "ui/Save/Load_BTN_pressed.png"
    );
    // MULTIPLAYER TEMP
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 14 / 20,
        350, 100,
        [](){
            is::Game::setActualScene(SCENE_MULTIPLAYER_HUB);
        },
        true,
        "ui/Multiplayer/multiplayer_BTN.png",
        "ui/Multiplayer/multiplayer_BTN_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 17 / 20,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        true,
        "ui/main_menu/button_quit.png",
        "ui/main_menu/button_quit_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(SCENE_CONTROLLERS);
        },
        true,
        "ui/main_menu/Controllers_BTN.png",
        "ui/main_menu/Controllers_BTN_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(SCENE_SETTINGS);
        },
        true,
        "ui/main_menu/Settings_BTN.png",
        "ui/main_menu/Settings_BTN_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(SCENE_HOWTOPLAY);
        },
        true,
        "ui/main_menu/FAQ_BTN.png",
        "ui/main_menu/FAQ_BTN_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(SCENE_CREDIT);
        },
        true,
        "ui/main_menu/Info_BTN.png",
        "ui/main_menu/Info_BTN_pressed.png"
    );
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createPause(std::shared_ptr<is::ecs::ComponentManager> &componentManager)
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        "ui/Pause/Pause.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 300 / 2, 300, true
    ).layer = 1;
    e->addComponent<ImageComponent>(
        e,
        "ui/Pause/logo.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2, 30, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 8 / 20,
        350, 100,
        [](){
            is::Game::setActualScene(SCENE_GAME, false, true);
        },
        true,
        "ui/Pause/Continue_BTN.png",
        "ui/Pause/Continue_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 11 / 20,
        350, 100,
        [&componentManager](){
            MapLoader::saveMap(RESSOURCE(".savemap"));
        },
        true,
        "ui/Save/Save_BTN.png",
        "ui/Save/Save_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 14 / 20,
        350, 100,
        [](){
            is::Game::setUnloadScene(SCENE_GAME);
            is::Game::setActualScene(SCENE_MAIN_MENU);
        },
        true,
        "ui/Pause/Menu_BTN.png",
        "ui/Pause/Menu_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 17 / 20,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        true,
        "ui/Pause/button_quit.png",
        "ui/Pause/button_quit_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(SCENE_SETTINGS);
        },
        true,
        "ui/Pause/Settings_BTN.png",
        "ui/Pause/Settings_BTN_pressed.png"
    ).layer = 2;
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createCredit()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        "ui/Credits/Information.png",
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
        "ui/Credits/Return_BTN.png",
        "ui/Credits/Return_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<TextComponent>(
        e,
        "Epitech Project Tek2",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 150,
        350, 100,
        true,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
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
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createHowToPlay()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ImageComponent>(
        e,
        "ui/HowToPlay/Header.png",
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
        "ui/HowToPlay/Return_BTN.png",
        "ui/HowToPlay/Return_BTN_pressed.png"
    ).layer = 1;
    e->addComponent<ImageComponent>(
        e,
        "ui/HowToPlay/HTP.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 1594 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20,
        true
    ).layer = 4;
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createMultiplayerHub(std::shared_ptr<NetworkComponent> nc)
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
        },
        true,
        "ui/Multiplayer/Return_BTN.png",
        "ui/Multiplayer/Return_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 300,
        350, 100,
        [nc](){
            is::Game::setActualScene(Scenes::SCENE_MULTIPLAYER_RULE_SETTINGS);
        },
        true,
        "ui/Multiplayer/create_lobby_BTN.png",
        "ui/Multiplayer/create_lobby_BTN_pressed.png"
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 50,
        350, 100,
        [](){
            is::Game::setActualScene(Scenes::SCENE_MULTIPLAYER_LOBBY_CHOICE);
        },
        true,
        "ui/Multiplayer/join_lobby_BTN.png",
        "ui/Multiplayer/join_lobby_BTN_pressed.png"
    );
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createMultiplayerLobbyChoice(const std::shared_ptr<NetworkComponent> &nc)
{
    auto e = std::make_shared<Entity>();

    e->addComponent<NumberFieldComponent>(e);
    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MULTIPLAYER_HUB);
        },
        true,
        "ui/Multiplayer/Return_BTN.png",
        "ui/Multiplayer/Return_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 300,
        350, 100,
        [nc, e](){
            nc->writeQueue.push("req jl " + std::to_string(e->getComponent<NumberFieldComponent>()->get()->getEnteredNumber()) + " \n");
        },
        true,
        "ui/main_menu/button_play.png",
        "ui/main_menu/button_play_pressed.png"
    );
    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createMultiplayerLobby(const std::shared_ptr<NetworkComponent> &nc)
{
    auto e = std::make_shared<Entity>();

    e->addComponent<ImageComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        0, -1, false
    ).layer = -9999;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MULTIPLAYER_HUB);
        },
        true,
        "ui/Multiplayer/Return_BTN.png",
        "ui/Multiplayer/Return_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 500,
        350, 100,
        [nc](){
            nc->writeQueue.push("req sg " + std::to_string(nc->lobby) + " \n");
        },
        true,
        "ui/main_menu/button_play.png",
        "ui/main_menu/button_play_pressed.png"
    );
    e->addComponent<TextComponent>(
        e,
        "Code to invite your friends: " + std::to_string(nc->lobby),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 130,
        350, 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    return e;
}
