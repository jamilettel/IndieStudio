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

static int selectedPreset = 0;

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createControllersBase()
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
        RESSOURCE("ui/Controllers/Controls_title.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 700 / 2, 50, true
    ).layer = 1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        30, 30,
        60, 60,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/Controllers/Return_BTN.png"),
        RESSOURCE("ui/Controllers/Return_BTN_pressed.png")
    ).layer = 2;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Controllers/Controller.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first - 350, 200,
        true
    ).layer = 1;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/Controllers/Keyboard.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2, 180,
        true
    ).layer = 1;
    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createControllersOptions()
{
    auto e = std::make_shared<is::ecs::Entity>();

    selectedPreset = 0;
    auto &TextPresetSelected = e->addComponent<is::components::TextComponent>(
        e,
        "Preset 1",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20 + 30,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        true
    );
    TextPresetSelected.layer = 2;

    auto &changePresetNext = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 5 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20,
        100, 100,
        [&TextPresetSelected](){
            if (selectedPreset == 3) {
                selectedPreset = 0;
                TextPresetSelected.setText("Preset 1");
                return;
            }
            selectedPreset++;
            TextPresetSelected.setText(std::string("Preset ") + std::to_string(selectedPreset + 1));
        },
        true,
        RESSOURCE("ui/PresetSelection/Forward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")
    );
    changePresetNext.layer = 3;

    auto &changePresetPrev = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 1 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20,
        100, 100,
        [&TextPresetSelected](){
            if (selectedPreset == 0) {
                selectedPreset = 3;
                TextPresetSelected.setText("Preset 4");
                return;
            }
            selectedPreset--;
            TextPresetSelected.setText(std::string("Preset ") + std::to_string(selectedPreset + 1));
        },
        true,
        RESSOURCE("ui/PresetSelection/Backward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")
    );
    changePresetPrev.layer = 3;
    return e;
}