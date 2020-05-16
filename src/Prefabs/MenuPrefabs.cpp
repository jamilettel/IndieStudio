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
    e->addComponent<WindowComponent>(e, "Indie Studio");
    e->addComponent<LightComponent>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0));
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
            is::Game::setActualScene(is::ecs::SCENE_CONTROLLERS);
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
            is::Game::setActualScene(is::ecs::SCENE_SETTINGS);
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
            is::Game::setActualScene(is::ecs::SCENE_CREDIT);
        },
        RESSOURCE("ui/main_menu/Info_BTN.png"),
        RESSOURCE("ui/main_menu/Info_BTN_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createSettings()
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
        RESSOURCE("ui/settings/Header.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 435 / 2, 50, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
        },
        RESSOURCE("ui/settings/Return_BTN.png"),
        RESSOURCE("ui/settings/Return_BTN_pressed.png")
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/settings/Window.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500, 250, true
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/settings/Music.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500 + 90, 262, true
    );
    std::string volumeMusic = std::to_string(is::components::AudioComponent::_volumeMusic);
    std::string volumeSound = std::to_string(is::components::AudioComponent::_volumeSound);
    auto &volumeMusicText = e->addComponent<is::components::TextComponent>(
        e,
        volumeMusic.erase(volumeMusic.find('.')),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500 + 150, 350,
        100, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    auto &volumeSoundText = e->addComponent<is::components::TextComponent>(
        e,
        volumeSound.erase(volumeSound.find('.')),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 500 - 180, 350,
        100, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500 + 140, 450,
        50, 50,
        [&volumeMusicText](){
            is::components::AudioComponent::_volumeMusic = 0;
            std::string text = std::to_string(is::components::AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_no_BTN.png"),
        RESSOURCE("ui/settings/Sound_no_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500 + 240, 350,
        50, 50,
        [&volumeMusicText](){
            if (is::components::AudioComponent::_volumeMusic > 99)
                return;
            is::components::AudioComponent::_volumeMusic++;
            std::string text = std::to_string(is::components::AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_high_BTN.png"),
        RESSOURCE("ui/settings/Sound_high_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 500 + 40, 350,
        50, 50,
        [&volumeMusicText](){
            if (is::components::AudioComponent::_volumeMusic < 1)
                return;
            is::components::AudioComponent::_volumeMusic--;
            std::string text = std::to_string(is::components::AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_low_BTN.png"),
        RESSOURCE("ui/settings/Sound_low_BTN_pressed.png")
    );

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/settings/Window.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 500 - 336, 250, true
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/settings/Sound.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 260, 265, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 500 - 190, 450,
        50, 50,
        [&volumeSoundText](){
            is::components::AudioComponent::_volumeSound = 0;
            std::string text = std::to_string(is::components::AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_no_BTN.png"),
        RESSOURCE("ui/settings/Sound_no_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 500 - 290, 350,
        50, 50,
        [&volumeSoundText](){
            if (is::components::AudioComponent::_volumeSound < 1)
                return;
            is::components::AudioComponent::_volumeSound--;
            std::string text = std::to_string(is::components::AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_low_BTN.png"),
        RESSOURCE("ui/settings/Sound_low_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 + 500 - 90, 350,
        50, 50,
        [&volumeSoundText](){
            if (is::components::AudioComponent::_volumeSound > 99)
                return;
            is::components::AudioComponent::_volumeSound++;
            std::string text = std::to_string(is::components::AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        RESSOURCE("ui/settings/Sound_high_BTN.png"),
        RESSOURCE("ui/settings/Sound_high_BTN_pressed.png")
    );
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createControllers()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/main_menu/background_main_menu.png"),
        "Indie Studio",
        0, 0, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
        },
        RESSOURCE("ui/controllers/Return_BTN.png"),
        RESSOURCE("ui/controllers/Return_BTN_pressed.png")
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
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_GAME);
        },
        RESSOURCE("ui/controllers/Return_BTN.png"),
        RESSOURCE("ui/controllers/Return_BTN_pressed.png")
    );
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
    );
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/credits/Information.png"),
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 606 / 2, 50, true
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        50, 50,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
        },
        RESSOURCE("ui/controllers/Return_BTN.png"),
        RESSOURCE("ui/controllers/Return_BTN_pressed.png")
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Epitech Project Tek2",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 150,
        350, 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 68, 68, 68)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Amaury Lecomte",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 280,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Benjamin Bourgeois",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 380,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Jamil Ettel",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 480,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Louis Deschanel",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 580,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Nathan Quentel",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 680,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<is::components::TextComponent>(
        e,
        "Tristan Bouillot",
        "Indie Studio",
        is::components::WindowComponent::_width / 2 - 350 / 2, 780,
        350, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    return e;
}
