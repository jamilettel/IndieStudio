/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Controllers Prefab
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"

using namespace is::ecs;
using namespace is::components;

static int selectedPreset = 0;

std::shared_ptr<Entity> is::prefabs::GlobalPrefabs::createControllersBase()
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
        "ui/Controllers/Controls_title.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 700 / 2, 40, true
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
        "ui/Controllers/Return_BTN.png",
        "ui/Controllers/Return_BTN_pressed.png"
    ).layer = 2;
    e->addComponent<ImageComponent>(
        e,
        "ui/Controllers/Controller.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 14 / 20,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 40 + 20,
        true
    ).layer = 1;
    e->addComponent<ImageComponent>(
        e,
        "ui/Controllers/Keyboard.png",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 8 / 20,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 40,
        true
    ).layer = 1;
    return e;
}

std::shared_ptr<Entity> is::prefabs::GlobalPrefabs::createControllersOptions(const ::ComponentManager &manager)
{
    auto e = std::make_shared<Entity>();
    auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());

    selectedPreset = 0;
    auto &TextPresetSelected = e->addComponent<TextComponent>(
        e,
        "Preset 1",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7 / 20,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 40 + 30,
        150, 40,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 255, 255, 255),
        true
    );
    TextPresetSelected.layer = 2;

    auto &changePresetNext = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 5 / 20,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 40,
        100, 100,
        [&manager, &TextPresetSelected](){
            const auto &p = std::static_pointer_cast<PresetComponent>(manager.getComponentsByType(typeid(PresetComponent).hash_code())[selectedPreset]);
            std::for_each(p->_textPreset.begin(), p->_textPreset.end(), [](auto &text){
                text.get().setVisible(false);
            });
            std::for_each(p->_imagePreset.begin(), p->_imagePreset.end(), [](auto &image){
                image.get().setVisible(false);
            });
            std::for_each(p->_buttonPreset.begin(), p->_buttonPreset.end(), [](auto &button){
                button.get().setVisible(false);
            });
            p->_onSelect = false;
            if (selectedPreset == 3) {
                selectedPreset = 0;
                TextPresetSelected.setText("Preset 1");
            } else {
                selectedPreset++;
                TextPresetSelected.setText(std::string("Preset ") + std::to_string(selectedPreset + 1));
            }
            const auto &np = std::static_pointer_cast<PresetComponent>(manager.getComponentsByType(typeid(PresetComponent).hash_code())[selectedPreset]);
            std::for_each(np->_textPreset.begin(), np->_textPreset.end(), [](auto &text){
                text.get().setVisible(true);
            });
            std::for_each(np->_imagePreset.begin(), np->_imagePreset.end(), [](auto &image){
                image.get().setVisible(true);
            });
            std::for_each(np->_buttonPreset.begin(), np->_buttonPreset.end(), [](auto &button){
                button.get().setVisible(true);
            });
            np->_onSelect = true;
        },
        true,
        "ui/Controllers/Forward_BTN.png",
        "ui/Controllers/Forward_BTN_pressed.png"
    );
    changePresetNext.layer = 3;

    auto &changePresetPrev = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 1 / 20,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 40,
        100, 100,
        [&manager, &TextPresetSelected](){
            const auto &p = std::static_pointer_cast<PresetComponent>(manager.getComponentsByType(typeid(PresetComponent).hash_code())[selectedPreset]);
            std::for_each(p->_textPreset.begin(), p->_textPreset.end(), [](auto &text){
                text.get().setVisible(false);
            });
            std::for_each(p->_imagePreset.begin(), p->_imagePreset.end(), [](auto &image){
                image.get().setVisible(false);
            });
            std::for_each(p->_buttonPreset.begin(), p->_buttonPreset.end(), [](auto &button){
                button.get().setVisible(false);
            });
            p->_onSelect = false;
            if (selectedPreset == 0) {
                selectedPreset = 3;
                TextPresetSelected.setText("Preset 4");
            } else {
                selectedPreset--;
                TextPresetSelected.setText(std::string("Preset ") + std::to_string(selectedPreset + 1));
            }
            const auto &np = std::static_pointer_cast<PresetComponent>(manager.getComponentsByType(typeid(PresetComponent).hash_code())[selectedPreset]);
            std::for_each(np->_textPreset.begin(), np->_textPreset.end(), [](auto &text){
                text.get().setVisible(true);
            });
            std::for_each(np->_imagePreset.begin(), np->_imagePreset.end(), [](auto &image){
                image.get().setVisible(true);
            });
            std::for_each(np->_buttonPreset.begin(), np->_buttonPreset.end(), [](auto &button){
                button.get().setVisible(true);
            });
            np->_onSelect = true;
        },
        true,
        "ui/Controllers/Backward_BTN.png",
        "ui/Controllers/Backward_BTN_pressed.png"
    );
    changePresetPrev.layer = 3;

    for (int i = 0; CharacterComponent::playerActions[i].value != -9999; i++) {

        int count = 0;

        auto &textAction = e->addComponent<TextComponent>(
            e,
            CharacterComponent::playerActions[i].description,
            "Indie Studio",
            WindowComponent::_windowsDimensions["Indie Studio"].first *
            1.9 / 20,
            WindowComponent::_windowsDimensions["Indie Studio"].second *
            4 / 20 + 20 + ((i + 1) * 100),
            300, 100,
            true,
            false,
            "fonts/fontVolumeSettings/fontVolumeSettings.xml",
            irr::video::SColor(255, 255, 255, 255),
            true
        );
        textAction.layer = 2;

        for (auto &preset : presets) {
            const auto &p = std::static_pointer_cast<PresetComponent>(preset);
            auto &keyboardBinds = p->getKeyboardPreset().getBindings();
            auto JoystickBinds = p->getJoystickPreset().getBindings();

            auto &keyboardAction = e->addComponent<TextComponent>(
                e,
                PresetComponent::getEquivalentKey(keyboardBinds.at(CharacterComponent::playerActions[i])),
                "Indie Studio",
                WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 20,
                WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20 + 20 + ((i + 1) * 100),
                140, 100,
                true,
                true,
                "fonts/fontVolumeSettings/fontVolumeSettings.xml",
                irr::video::SColor(255, 255, 255, 255),
                count == 0
            );
            keyboardAction.layer = 2;

            auto &controllerAction = e->addComponent<ImageComponent>(
                e,
                PresetComponent::getEquivalentButton(JoystickBinds.at(CharacterComponent::playerActions[i])),
                "Indie Studio",
                WindowComponent::_windowsDimensions["Indie Studio"].first * 29 / 40 - 10,
                WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20 + 30 + ((i + 1) * 100),
                true,
                count == 0
            );

            auto &buttonAction = e->addComponent<ButtonComponent>(
                e,
                "",
                "Indie Studio",
                WindowComponent::_windowsDimensions["Indie Studio"].first * 17 / 20,
                WindowComponent::_windowsDimensions["Indie Studio"].second * 4 / 20 + 40 + ((i + 1) * 100),
                220, 70,
                []() {
                },
                count == 0,
                "ui/Controllers/Change_BTN.png",
                "ui/Controllers/Change_BTN_pressed.png"
            );
            buttonAction.layer = 3;
            buttonAction.setCallback([&buttonAction, &keyboardAction, &controllerAction, p, i](){
                p->_toChange.emplace(CharacterComponent::playerActions[i]);
                p->_toChangeUI = std::tuple<std::reference_wrapper<TextComponent>, std::reference_wrapper<ImageComponent>, std::reference_wrapper<ButtonComponent>>(keyboardAction, controllerAction, buttonAction);
                p->_callerID = buttonAction.getCallerId();
            });
            p->_textPreset.emplace_back(keyboardAction);
            p->_imagePreset.emplace_back(controllerAction);
            p->_buttonPreset.emplace_back(buttonAction);
            count++;
        }
    }
    return e;
}
