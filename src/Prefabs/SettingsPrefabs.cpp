/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Settings Prefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"

using namespace is::ecs;
using namespace is::components;

std::shared_ptr<Entity> is::prefabs::GlobalPrefabs::createSettings()
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
        "ui/settings/Header.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 435 / 2, 50, true
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
        "ui/settings/Return_BTN.png",
        "ui/settings/Return_BTN_pressed.png"
    ).layer = 3;
    e->addComponent<ImageComponent>(
        e,
        "ui/settings/Window.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500, 250, true
    ).layer = 2;
    e->addComponent<ImageComponent>(
        e,
        "ui/settings/Music.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500 + 90, 262, true
    ).layer = 2;
    std::string volumeMusic = std::to_string(AudioComponent::_volumeMusic);
    std::string volumeSound = std::to_string(AudioComponent::_volumeSound);
    auto &volumeMusicText = e->addComponent<TextComponent>(
        e,
        volumeMusic.erase(volumeMusic.find('.')),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500 + 120, 325,
        100, 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    );
    auto &volumeSoundText = e->addComponent<TextComponent>(
        e,
        volumeSound.erase(volumeSound.find('.')),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 500 - 210, 325,
        100, 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    );
    volumeSoundText.layer = 4;
    volumeMusicText.layer = 4;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500 + 140, 450,
        50, 50,
        [&volumeMusicText](){
            AudioComponent::_volumeMusic = 0;
            std::string text = std::to_string(AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_no_BTN.png",
        "ui/settings/Sound_no_BTN_pressed.png"
    ).layer = 3;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500 + 240, 350,
        50, 50,
        [&volumeMusicText](){
            if (AudioComponent::_volumeMusic > 99)
                return;
            AudioComponent::_volumeMusic++;
            std::string text = std::to_string(AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_high_BTN.png",
        "ui/settings/Sound_high_BTN_pressed.png"
    ).layer = 3;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 500 + 40, 350,
        50, 50,
        [&volumeMusicText](){
            if (AudioComponent::_volumeMusic < 1)
                return;
            AudioComponent::_volumeMusic--;
            std::string text = std::to_string(AudioComponent::_volumeMusic);
            volumeMusicText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_low_BTN.png",
        "ui/settings/Sound_low_BTN_pressed.png"
    ).layer = 3;

    e->addComponent<ImageComponent>(
        e,
        "ui/settings/Window.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 500 - 336, 250, true
    ).layer = 1;
    e->addComponent<ImageComponent>(
        e,
        "ui/settings/Sound.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 260, 265, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 500 - 190, 450,
        50, 50,
        [&volumeSoundText](){
            AudioComponent::_volumeSound = 0;
            std::string text = std::to_string(AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_no_BTN.png",
        "ui/settings/Sound_no_BTN_pressed.png"
    ).layer = 3;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 500 - 290, 350,
        50, 50,
        [&volumeSoundText](){
            if (AudioComponent::_volumeSound < 1)
                return;
            AudioComponent::_volumeSound--;
            std::string text = std::to_string(AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_low_BTN.png",
        "ui/settings/Sound_low_BTN_pressed.png"
    ).layer = 3;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 500 - 90, 350,
        50, 50,
        [&volumeSoundText](){
            if (AudioComponent::_volumeSound > 99)
                return;
            AudioComponent::_volumeSound++;
            std::string text = std::to_string(AudioComponent::_volumeSound);
            volumeSoundText.setText(text.erase(text.find('.')));
        },
        true,
        "ui/settings/Sound_high_BTN.png",
        "ui/settings/Sound_high_BTN_pressed.png"
    ).layer = 3;
    return e;
}
