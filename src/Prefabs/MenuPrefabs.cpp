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

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<TimeComponent>(e);
    e->addComponent<AudioComponent>(e, RESSOURCE("lol.wav"), MUSIC, false);
    auto &window = e->addComponent<WindowComponent>(e, "Indie Studio");
    auto &cursor = e->addComponent<ImageComponent>(e, RESSOURCE("/ui/cursor/cursor.png"), "Indie Studio", 0, 0);
    cursor.layer = 10;
    e->addComponent<CursorComponent>(e, cursor, window);
    e->addComponent<LightComponent>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0), true);
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createSplashScreen()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/splashscreen.png"),
        "Indie Studio",
        0, 0, true
    ).layer = 9999;
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
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/logo.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2, 50, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 50,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/main_menu/button_play.png"),
        RESSOURCE("ui/main_menu/button_play_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 200,
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
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_CONTROLLERS);
        },
        RESSOURCE("ui/main_menu/Controllers_BTN.png"),
        RESSOURCE("ui/main_menu/Controllers_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_SETTINGS);
        },
        RESSOURCE("ui/main_menu/Settings_BTN.png"),
        RESSOURCE("ui/main_menu/Settings_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 50 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 100,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_RECORD);
        },
        RESSOURCE("ui/main_menu/Scores_BTN.png"),
        RESSOURCE("ui/main_menu/Scores_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 150,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_HOWTOPLAY);
        },
        RESSOURCE("ui/main_menu/FAQ_BTN.png"),
        RESSOURCE("ui/main_menu/FAQ_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_CREDIT);
        },
        RESSOURCE("ui/main_menu/Info_BTN.png"),
        RESSOURCE("ui/main_menu/Info_BTN_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createPause()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Pause/Pause.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 300 / 2, 300, true
    ).layer = 1;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Pause/logo.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 541 / 2, 30, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 100,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_GAME);
        },
        RESSOURCE("ui/Pause/Continue_BTN.png"),
        RESSOURCE("ui/Pause/Continue_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 2.5 + 250,
        350, 100,
        [](){
            is::Game::isRunning = false;
        },
        RESSOURCE("ui/Pause/button_quit.png"),
        RESSOURCE("ui/Pause/button_quit_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first - 80,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 70,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_SETTINGS);
        },
        RESSOURCE("ui/Pause/Settings_BTN.png"),
        RESSOURCE("ui/Pause/Settings_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 50 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 100,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_RECORD);
        },
        RESSOURCE("ui/Pause/Scores_BTN.png"),
        RESSOURCE("ui/Pause/Scores_BTN_pressed.png")
    ).layer = 2;
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createCredit()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Credits/Information.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 606 / 2, 50, true
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
        RESSOURCE("ui/Credits/Return_BTN.png"),
        RESSOURCE("ui/Credits/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<is::components::TextComponent>(
        e,
        "Epitech Project Tek2",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 150,
        350, 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 68, 68, 68)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Amaury Lecomte",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 280,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Benjamin Bourgeois",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 380,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Jamil Ettel",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 480,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Louis Deschanel",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 580,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Nathan Quentel",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 680,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Tristan Bouillot",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 780,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    ).layer = 4;
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createHowToPlay()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
        "Indie Studio",
        0, 0, true
    ).layer = -9999;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/HowToPlay/Header.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 700 / 2, 50, true
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
        RESSOURCE("ui/HowToPlay/Return_BTN.png"),
        RESSOURCE("ui/HowToPlay/Return_BTN_pressed.png")
    ).layer = 2;
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createRecord()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
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
        RESSOURCE("ui/Record/Return_BTN.png"),
        RESSOURCE("ui/Record/Return_BTN_pressed.png")
    ).layer = 2;
    return e;
}
