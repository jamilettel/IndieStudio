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

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createPresetSelectionBase()
{
    auto e = std::make_shared<is::ecs::Entity>();

    /* BACKGROUND AND RETURN BUTTON */
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        0, 0, true
    ).layer = -1;
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 350 / 2,
        50,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_GAME);
        },
        true,
        RESSOURCE("ui/PresetSelection/button_play.png"),
        RESSOURCE("ui/PresetSelection/button_play_pressed.png")
    );

    /* BUTTON PLAY */
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
        RESSOURCE("ui/PresetSelection/Return_BTN.png"),
        RESSOURCE("ui/PresetSelection/Return_BTN_pressed.png")
    ).layer = 2;

    /* BACKGROUND FOR EACH PLAYER */
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/Box.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3,
        true
    ).layer = 1;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/Box.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3,
        true
    ).layer = 1;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/Box.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400,
        true
    ).layer = 1;
    e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/Box.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400,
        true
    ).layer = 1;

    /* TITLE PLAYER */
    e->addComponent<is::components::TextComponent>(
        e,
        "Player 1",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 250,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Player 3",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 250,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400 + 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Player 2",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 250,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    ).layer = 4;
    e->addComponent<is::components::TextComponent>(
        e,
        "Player 4",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 250,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400 + 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    ).layer = 4;

    return e;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createPresetSelectionOptions(const is::ecs::ComponentManager &manager)
{
    auto e = std::make_shared<is::ecs::Entity>();
    const auto &characterList = manager.getComponentsByType(typeid(CharacterComponent).hash_code());

    /* PLAYER 1 */
    auto &IAImage1 = e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/AI.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40 + 50,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140 - 100,
        true
    );
    IAImage1.layer = 2;
    auto &TextIA1 =e->addComponent<is::components::TextComponent>(
        e,
        "AI",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40 + 70,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140 - 80,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    );
    TextIA1.layer = 2;
    auto &textPreset1 = e->addComponent<is::components::TextComponent>(
        e,
        "Preset",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        false
    );
    textPreset1.layer = 4;
    auto &textController1 = e->addComponent<is::components::TextComponent>(
        e,
        "Keyboard",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 7.5 / 40,
        160, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 0, 0, 0),
        false
    );
    textController1.layer = 4;
    auto &activateButton1 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140,
        250, 70,
        [](){
        },
        true,
        RESSOURCE("ui/PresetSelection/Activate_BTN.png"),
        RESSOURCE("ui/PresetSelection/Activate_BTN_pressed.png")
    );
    auto &closeButton1 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 80 - 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Close_BTN.png"),
        RESSOURCE("ui/PresetSelection/Close_BTN_pressed.png")
    );
    auto &leftPresetButton1 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 5 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Backward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")
    );
    auto &rightPresetButton1 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Forward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")
    );
    auto characterComponent1 = static_cast<CharacterComponent*>(characterList[0].get());
    activateButton1.layer = 3;
    activateButton1.setCallback([&activateButton1, &TextIA1, &IAImage1, &closeButton1, &leftPresetButton1, &rightPresetButton1, &textPreset1, &textController1, characterComponent1](){
        activateButton1.setVisible(false);
        TextIA1.setVisible(false);
        IAImage1.setVisible(false);
        closeButton1.setVisible(true);
        leftPresetButton1.setVisible(true);
        rightPresetButton1.setVisible(true);
        textPreset1.setVisible(true);
        textController1.setVisible(false);
        textController1.setVisible(true);
        characterComponent1->presetNumber = 1;
        characterComponent1->characterType = CharacterComponent::KEYBOARD_PLAYER;
        textPreset1.setText("Preset 1");
    });
    closeButton1.layer = 3;
    closeButton1.setCallback([&activateButton1, &TextIA1, &IAImage1, &closeButton1, &leftPresetButton1, &rightPresetButton1, &textPreset1, &textController1, characterComponent1](){
        activateButton1.setVisible(true);
        TextIA1.setVisible(true);
        IAImage1.setVisible(true);
        closeButton1.setVisible(false);
        leftPresetButton1.setVisible(false);
        rightPresetButton1.setVisible(false);
        textPreset1.setVisible(false);
        textController1.setVisible(false);
        characterComponent1->presetNumber = -1;
        characterComponent1->characterType = CharacterComponent::AI;
    });
    rightPresetButton1.setCallback([&textPreset1, characterComponent1](){
        if (characterComponent1->presetNumber == 4) {
            characterComponent1->presetNumber = 1;
            textPreset1.setText("Preset 1");
            return;
        }
        characterComponent1->presetNumber++;
        textPreset1.setText(std::string("Preset ") + std::to_string(characterComponent1->presetNumber));
    });
    leftPresetButton1.setCallback([&textPreset1, characterComponent1](){
        if (characterComponent1->presetNumber == 1) {
            characterComponent1->presetNumber = 4;
            textPreset1.setText("Preset 4");
            return;
        }
        characterComponent1->presetNumber--;
        textPreset1.setText(std::string("Preset ") + std::to_string(characterComponent1->presetNumber));
    });
    leftPresetButton1.layer = 3;
    rightPresetButton1.layer = 3;

    /* PLAYER 2 */
    auto &IAImage2 = e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/AI.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40 + 50,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140 - 100,
        true
    );
    IAImage2.layer = 2;
    auto &TextIA2 = e->addComponent<is::components::TextComponent>(
        e,
        "AI",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40 + 70,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140 - 80,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    );
    TextIA2.layer = 2;
    auto &textPreset2 = e->addComponent<is::components::TextComponent>(
        e,
        "Preset",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 14 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        false
    );
    textPreset2.layer = 4;
    auto &textController2 = e->addComponent<is::components::TextComponent>(
        e,
        "Keyboard",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 14 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 7.5 / 40,
        160, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 0, 0, 0),
        false
    );
    textController2.layer = 4;
    auto &activateButton2 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 332 - 140,
        250, 70,
        [](){
        },
        true,
        RESSOURCE("ui/PresetSelection/Activate_BTN.png"),
        RESSOURCE("ui/PresetSelection/Activate_BTN_pressed.png")
    );
    auto &closeButton2 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 570,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Close_BTN.png"),
        RESSOURCE("ui/PresetSelection/Close_BTN_pressed.png")
    );
    auto &leftPresetButton2 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 12 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Backward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")
    );
    auto &rightPresetButton2 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 17 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second / 3 - 332 / 3 + 190,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Forward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")
    );
    auto characterComponent2 = static_cast<CharacterComponent*>(characterList[1].get());
    activateButton2.layer = 3;
    activateButton2.setCallback([&activateButton2, &TextIA2, &IAImage2, &closeButton2, &leftPresetButton2, &rightPresetButton2, &textPreset2, &textController2, characterComponent2](){
        activateButton2.setVisible(false);
        TextIA2.setVisible(false);
        IAImage2.setVisible(false);
        closeButton2.setVisible(true);
        leftPresetButton2.setVisible(true);
        rightPresetButton2.setVisible(true);
        textPreset2.setVisible(true);
        textController2.setVisible(true);
        characterComponent2->presetNumber = 1;
        characterComponent2->characterType = CharacterComponent::KEYBOARD_PLAYER;
        textPreset2.setText("Preset 1");
    });
    closeButton2.layer = 3;
    closeButton2.setCallback([&activateButton2, &TextIA2, &IAImage2, &closeButton2, &leftPresetButton2, &rightPresetButton2, &textPreset2, &textController2, characterComponent2](){
        activateButton2.setVisible(true);
        TextIA2.setVisible(true);
        IAImage2.setVisible(true);
        closeButton2.setVisible(false);
        leftPresetButton2.setVisible(false);
        rightPresetButton2.setVisible(false);
        textPreset2.setVisible(false);
        textController2.setVisible(false);
        characterComponent2->presetNumber = -1;
        characterComponent2->characterType = CharacterComponent::AI;
    });
    rightPresetButton2.setCallback([&textPreset2, characterComponent2](){
        if (characterComponent2->presetNumber == 4) {
            characterComponent2->presetNumber = 1;
            textPreset2.setText("Preset 1");
            return;
        }
        characterComponent2->presetNumber++;
        textPreset2.setText(std::string("Preset ") + std::to_string(characterComponent2->presetNumber));
    });
    leftPresetButton2.setCallback([&textPreset2, characterComponent2](){
        if (characterComponent2->presetNumber == 1) {
            characterComponent2->presetNumber = 4;
            textPreset2.setText("Preset 4");
            return;
        }
        characterComponent2->presetNumber--;
        textPreset2.setText(std::string("Preset ") + std::to_string(characterComponent2->presetNumber));
    });
    leftPresetButton2.layer = 3;
    rightPresetButton2.layer = 3;

    /* PLAYER 3 */
    auto &IAImage3 = e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/AI.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40 + 50,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200 - 100,
        true
    );
    IAImage3.layer = 2;
    auto &TextIA3 = e->addComponent<is::components::TextComponent>(
        e,
        "AI",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40 + 70,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200 - 80,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    );
    TextIA3.layer = 2;
    auto &textPreset3 = e->addComponent<is::components::TextComponent>(
        e,
        "Preset",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        false
    );
    textPreset3.layer = 4;
    auto &textController3 = e->addComponent<is::components::TextComponent>(
        e,
        "Keyboard",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 29 / 40,
        160, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 0, 0, 0),
        false
    );
    textController3.layer = 4;
    auto &activateButton3 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 650 - 250 / 2 + 650 / 2 - 332 / 2 + 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200,
        250, 70,
        [](){
        },
        true,
        RESSOURCE("ui/PresetSelection/Activate_BTN.png"),
        RESSOURCE("ui/PresetSelection/Activate_BTN_pressed.png")
    );
    auto &closeButton3 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 80 - 250 / 2,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400 + 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Close_BTN.png"),
        RESSOURCE("ui/PresetSelection/Close_BTN_pressed.png")
    );
    auto &leftPresetButton3 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 5 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Backward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")
    );
    auto &rightPresetButton3 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Forward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")
    );
    auto characterComponent3 = static_cast<CharacterComponent*>(characterList[2].get());
    activateButton3.layer = 3;
    activateButton3.setCallback([&activateButton3, &TextIA3, &IAImage3, &closeButton3, &leftPresetButton3, &rightPresetButton3, &textPreset3, &textController3, characterComponent3](){
        activateButton3.setVisible(false);
        TextIA3.setVisible(false);
        IAImage3.setVisible(false);
        closeButton3.setVisible(true);
        leftPresetButton3.setVisible(true);
        rightPresetButton3.setVisible(true);
        textPreset3.setVisible(true);
        textController3.setVisible(true);
        characterComponent3->presetNumber = 1;
        characterComponent3->characterType = CharacterComponent::KEYBOARD_PLAYER;
        textPreset3.setText("Preset 1");
    });
    closeButton3.layer = 3;
    closeButton3.setCallback([&activateButton3, &TextIA3, &IAImage3, &closeButton3, &leftPresetButton3, &rightPresetButton3, &textPreset3, &textController3, characterComponent3](){
        activateButton3.setVisible(true);
        TextIA3.setVisible(true);
        IAImage3.setVisible(true);
        closeButton3.setVisible(false);
        leftPresetButton3.setVisible(false);
        rightPresetButton3.setVisible(false);
        textPreset3.setVisible(false);
        textController3.setVisible(false);
        characterComponent3->presetNumber = -1;
        characterComponent3->characterType = CharacterComponent::AI;
    });
    rightPresetButton3.setCallback([&textPreset3, characterComponent3](){
        if (characterComponent3->presetNumber == 4) {
            characterComponent3->presetNumber = 1;
            textPreset3.setText("Preset 1");
            return;
        }
        characterComponent3->presetNumber++;
        textPreset3.setText(std::string("Preset ") + std::to_string(characterComponent3->presetNumber));
    });
    leftPresetButton3.setCallback([&textPreset3, characterComponent3](){
        if (characterComponent3->presetNumber == 1) {
            characterComponent3->presetNumber = 4;
            textPreset3.setText("Preset 4");
            return;
        }
        characterComponent3->presetNumber--;
        textPreset3.setText(std::string("Preset ") + std::to_string(characterComponent3->presetNumber));
    });
    leftPresetButton3.layer = 3;
    rightPresetButton3.layer = 3;

    /* PLAYER 4 */
    auto &IAImage4 = e->addComponent<is::components::ImageComponent>(
        e,
        RESSOURCE("ui/PresetSelection/AI.png"),
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40 + 50,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200 - 100,
        true
    );
    IAImage4.layer = 2;
    auto &TextIA4 = e->addComponent<is::components::TextComponent>(
        e,
        "AI",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40 + 70,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200 - 80,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    );
    TextIA4.layer = 2;
    auto &textPreset4 = e->addComponent<is::components::TextComponent>(
        e,
        "Preset",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 14 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        150, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255),
        false
    );
    textPreset4.layer = 4;
    auto &textController4 = e->addComponent<is::components::TextComponent>(
        e,
        "Keyboard",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 14 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 29 / 40,
        160, 40,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 0, 0, 0),
        false
    );
    textController4.layer = 4;
    auto &activateButton4 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 650 / 2 - 332 / 2 + 40,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 200,
        250, 70,
        [](){
        },
        true,
        RESSOURCE("ui/PresetSelection/Activate_BTN.png"),
        RESSOURCE("ui/PresetSelection/Activate_BTN_pressed.png")
    );
    auto &closeButton4 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 + 250 / 2 + 570,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second - 400 + 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Close_BTN.png"),
        RESSOURCE("ui/PresetSelection/Close_BTN_pressed.png")
    );
    auto &leftPresetButton4 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 12 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Backward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")
    );
    auto &rightPresetButton4 = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first * 17 / 20,
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].second * 16 / 20,
        50, 50,
        [](){
        },
        false,
        RESSOURCE("ui/PresetSelection/Forward_BTN.png"),
        RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")
    );
    auto characterComponent4 = static_cast<CharacterComponent*>(characterList[3].get());
    activateButton4.layer = 3;
    activateButton4.setCallback([&activateButton4, &TextIA4, &IAImage4, &closeButton4, &leftPresetButton4, &rightPresetButton4, &textPreset4, &textController4, characterComponent4](){
        activateButton4.setVisible(false);
        TextIA4.setVisible(false);
        IAImage4.setVisible(false);
        closeButton4.setVisible(true);
        leftPresetButton4.setVisible(true);
        rightPresetButton4.setVisible(true);
        textPreset4.setVisible(true);
        textController4.setVisible(true);
        characterComponent4->presetNumber = 1;
        characterComponent4->characterType = CharacterComponent::KEYBOARD_PLAYER;
        textPreset4.setText("Preset 1");
    });
    closeButton4.layer = 3;
    closeButton4.setCallback([&activateButton4, &TextIA4, &IAImage4, &closeButton4, &leftPresetButton4, &rightPresetButton4, &textPreset4, &textController4, characterComponent4](){
        activateButton4.setVisible(true);
        TextIA4.setVisible(true);
        IAImage4.setVisible(true);
        closeButton4.setVisible(false);
        leftPresetButton4.setVisible(false);
        rightPresetButton4.setVisible(false);
        textPreset4.setVisible(false);
        textController4.setVisible(false);
        characterComponent4->presetNumber = -1;
        characterComponent4->characterType = CharacterComponent::AI;
    });
    rightPresetButton4.setCallback([&textPreset4, characterComponent4](){
        if (characterComponent4->presetNumber == 4) {
            characterComponent4->presetNumber = 1;
            textPreset4.setText("Preset 1");
            return;
        }
        characterComponent4->presetNumber++;
        textPreset4.setText(std::string("Preset ") + std::to_string(characterComponent4->presetNumber));
    });
    leftPresetButton4.setCallback([&textPreset4, characterComponent4](){
        if (characterComponent4->presetNumber == 1) {
            characterComponent4->presetNumber = 4;
            textPreset4.setText("Preset 4");
            return;
        }
        characterComponent4->presetNumber--;
        textPreset4.setText(std::string("Preset ") + std::to_string(characterComponent4->presetNumber));
    });
    leftPresetButton4.layer = 3;
    rightPresetButton4.layer = 3;
    return e;
}
