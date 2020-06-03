/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#include "Prefabs/RuleSettingsPrefabs.hpp"
#include <iostream>

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::prefabs;
using namespace is::ecs;
using namespace is::exceptions;
using namespace is::components;

std::shared_ptr<is::ecs::Entity>  RuleSettingsPrefabs::createBackground()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        irr::core::vector2df(0, -1),
        irr::core::vector2df(100, 120)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createReturnButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 2 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){
            is::Game::setActualScene(is::Game::getPreviousScene());
        },
        true,
        RESSOURCE("ui/RuleSettings/Return_BTN.png"),
        RESSOURCE("ui/RuleSettings/Return_BTN_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createRuleSettings()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<RulesSettingComponent>(e);
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createSettingsBackground(is::components::RulesSettingComponent &component)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table.png"),
        "Indie Studio",
        irr::core::vector2df(10, 20),
        irr::core::vector2df(35, 70)
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 26 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 23 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&component](){
            component.down();
        },
        true,
        RESSOURCE("ui/RuleSettings/Upward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Upward_BTN_pressed.png")
    );
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 26 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 80 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&component](){
            component.up();
        },
        true,
        RESSOURCE("ui/RuleSettings/Downward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Downward_BTN_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createNumberOfPlayersRule(is::components::RulesSettingComponent &component, RulesComponent &rules)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Dot_01.png"),
        "Indie Studio",
        irr::core::vector2df(11.3, 36),
        irr::core::vector2df(3, 5)
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 35),
        irr::core::vector2df(20, 8)
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 35),
        irr::core::vector2df(7, 8)
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Number of players",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 35 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 20 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getNumberOfPlayers()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 35.3f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getNumberOfPlayers()),
        "Indie Studio",
        1350, 480,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1200,
        550,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            if (rules.getNumberOfPlayers() > 2) {
                rules.setNumberOfPlayers(rules.getNumberOfPlayers() - 1);
                value.setText(std::to_string(rules.getNumberOfPlayers()));
                valueToChange.setText(std::to_string(rules.getNumberOfPlayers()));
            }
        },
        true,
        RESSOURCE("ui/RuleSettings/Backward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Backward_BTN_pressed.png")
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1550,
        550,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            if (rules.getNumberOfPlayers() < 4) {
                rules.setNumberOfPlayers(rules.getNumberOfPlayers() + 1);
                value.setText(std::to_string(rules.getNumberOfPlayers()));
                valueToChange.setText(std::to_string(rules.getNumberOfPlayers()));
            }
        },
        true,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );
    component.addRule(
        // On select
        [&dot, &backward, &forward, &valueToChange](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
            valueToChange.setVisible(true);
        },
        // On exit
        [&dot, &backward, &forward, &valueToChange](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
            valueToChange.setVisible(false);
        },
        // On disappear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(false);
            secondTable.setVisible(false);
            title.setVisible(false);
            value.setVisible(false);
        },
        // On rule up
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y - 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y - 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y - 10));
            title.move(irr::core::vector2di(0, -105));
            value.move(irr::core::vector2di(0, -105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.move(irr::core::vector2di(0, 105));
            value.move(irr::core::vector2di(0, 105));
        },
        // On appear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(true);
            secondTable.setVisible(true);
            title.setVisible(true);
            value.setVisible(true);
        }
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createIconsRule(is::components::RulesSettingComponent &component, RulesComponent &rules)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Dot_01.png"),
        "Indie Studio",
        irr::core::vector2df(11.3, 46),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 45),
        irr::core::vector2df(20, 8)
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 45),
        irr::core::vector2df(7, 8)
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Icons",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 45 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        (rules.noIconUsed() ? "Off" : "On"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 45.3f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        (rules.noIconUsed() ? "Off" : "On"),
        "Indie Studio",
        1380, 285,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    TextureComponent &onOff = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(71, 33),
        irr::core::vector2df(7, 8),
        false
    );
    TextureComponent &highBox = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Box.png"),
        "Indie Studio",
        irr::core::vector2df(60, 45),
        irr::core::vector2df(30, 25),
        false
    );

    ButtonComponent &acceleratorDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1200,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    acceleratorDisable.layer = 1;
    acceleratorDisable.setDisabled(true);
    ButtonComponent &accelerator = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1200,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/accelerator.png"),
        RESSOURCE("ui/RuleSettings/accelerator.png")
    );
    accelerator.setCallback([&accelerator, &acceleratorDisable, &rules, &value, &valueToChange](){
        accelerator.setDisabled(true);
        acceleratorDisable.setDisabled(false);
        acceleratorDisable.setVisible(true);
        rules.setIconUse(RulesComponent::ACCELERATOR, false);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });
    acceleratorDisable.setCallback([&accelerator, &acceleratorDisable, &rules, &value, &valueToChange](){
        accelerator.setDisabled(false);
        acceleratorDisable.setDisabled(true);
        acceleratorDisable.setVisible(false);
        rules.setIconUse(RulesComponent::ACCELERATOR, true);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });

    ButtonComponent &bombDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1270,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    bombDisable.layer = 1;
    bombDisable.setDisabled(true);
    ButtonComponent &bomb = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1270,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/bomb.png"),
        RESSOURCE("ui/RuleSettings/bomb.png")
    );
    bomb.setCallback([&bomb, &bombDisable, &rules, &value, &valueToChange](){
        bomb.setDisabled(true);
        bombDisable.setDisabled(false);
        bombDisable.setVisible(true);
        rules.setIconUse(RulesComponent::BOMB, false);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });
    bombDisable.setCallback([&bomb, &bombDisable, &rules, &value, &valueToChange](){
        bomb.setDisabled(false);
        bombDisable.setDisabled(true);
        bombDisable.setVisible(false);
        rules.setIconUse(RulesComponent::BOMB, true);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });

    ButtonComponent &explosionDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1340,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    explosionDisable.layer = 1;
    explosionDisable.setDisabled(true);
    ButtonComponent &explosion = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1340,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/explosion_expander.png"),
        RESSOURCE("ui/RuleSettings/explosion_expander.png")
    );
    explosion.setCallback([&explosion, &explosionDisable, &rules, &value, &valueToChange](){
        explosion.setDisabled(true);
        explosionDisable.setDisabled(false);
        explosionDisable.setVisible(true);
        rules.setIconUse(RulesComponent::EXPLOSION, false);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });
    explosionDisable.setCallback([&explosion, &explosionDisable, &rules, &value, &valueToChange](){
        explosion.setDisabled(false);
        explosionDisable.setDisabled(true);
        explosionDisable.setVisible(false);
        rules.setIconUse(RulesComponent::EXPLOSION, true);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });

    ButtonComponent &wallPassDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1410,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    wallPassDisable.layer = 1;
    wallPassDisable.setDisabled(true);
    ButtonComponent &wallPass = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1410,
        510,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/wall_pass.png"),
        RESSOURCE("ui/RuleSettings/wall_pass.png")
    );
    wallPass.setCallback([&wallPass, &wallPassDisable, &rules, &value, &valueToChange](){
        wallPass.setDisabled(true);
        wallPassDisable.setDisabled(false);
        wallPassDisable.setVisible(true);
        rules.setIconUse(RulesComponent::WALL_PASS, false);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });
    wallPassDisable.setCallback([&wallPass, &wallPassDisable, &rules, &value, &valueToChange](){
        wallPass.setDisabled(false);
        wallPassDisable.setDisabled(true);
        wallPassDisable.setVisible(false);
        rules.setIconUse(RulesComponent::WALL_PASS, true);
        value.setText((rules.noIconUsed() ? "Off" : "On"));
        valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
    });

    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1250,
        360,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable](){
            rules.setAllICons(rules.noIconUsed() ? true : false);
            value.setText((rules.noIconUsed() ? "Off" : "On"));
            valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
            if (rules.noIconUsed()) {
                wallPass.setClicked(true);
                accelerator.setClicked(true);
                bomb.setClicked(true);
                explosion.setClicked(true);
            } else {
                wallPassDisable.setClicked(true);
                acceleratorDisable.setClicked(true);
                bombDisable.setClicked(true);
                explosionDisable.setClicked(true);
            }
        },
        false,
        RESSOURCE("ui/RuleSettings/Backward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Backward_BTN_pressed.png")
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1550,
        360,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable](){
            rules.setAllICons(rules.noIconUsed() ? true : false);
            value.setText((rules.noIconUsed() ? "Off" : "On"));
            valueToChange.setText((rules.noIconUsed() ? "Off" : "On"));
            if (rules.noIconUsed()) {
                wallPass.setClicked(true);
                accelerator.setClicked(true);
                bomb.setClicked(true);
                explosion.setClicked(true);
            } else {
                wallPassDisable.setClicked(true);
                acceleratorDisable.setClicked(true);
                bombDisable.setClicked(true);
                explosionDisable.setClicked(true);
            }
        },
        false,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );

    component.addRule(
        // On select
        [&dot, &forward, &backward, &onOff, &highBox, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable, &valueToChange](){
            dot.setVisible(true);
            forward.setVisible(true);
            backward.setVisible(true);
            valueToChange.setVisible(true);
            onOff.setVisible(true);
            highBox.setVisible(true);
            accelerator.setVisible(true);
            bomb.setVisible(true);
            explosion.setVisible(true);
            wallPass.setVisible(true);
            if (!acceleratorDisable.isDisabled())
                acceleratorDisable.setVisible(true);
            if (!bombDisable.isDisabled())
                bombDisable.setVisible(true);
            if (!explosionDisable.isDisabled())
                explosionDisable.setVisible(true);
            if (!wallPassDisable.isDisabled())
                wallPassDisable.setVisible(true);
        },
        // On Exit
        [&dot, &forward, &backward, &onOff, &highBox, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable, &valueToChange](){
            dot.setVisible(false);
            forward.setVisible(false);
            backward.setVisible(false);
            valueToChange.setVisible(false);
            onOff.setVisible(false);
            highBox.setVisible(false);
            accelerator.setVisible(false);
            bomb.setVisible(false);
            explosion.setVisible(false);
            wallPass.setVisible(false);
            acceleratorDisable.setVisible(false);
            bombDisable.setVisible(false);
            explosionDisable.setVisible(false);
            wallPassDisable.setVisible(false);
        },
        // On disappear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(false);
            secondTable.setVisible(false);
            title.setVisible(false);
            value.setVisible(false);
        },
        // On rule up
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y - 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y - 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y - 10));
            title.move(irr::core::vector2di(0, -105));
            value.move(irr::core::vector2di(0, -105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.move(irr::core::vector2di(0, 105));
            value.move(irr::core::vector2di(0, 105));
        },
        // On appear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(true);
            secondTable.setVisible(true);
            title.setVisible(true);
            value.setVisible(true);
        }
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createMaxTimeRule(is::components::RulesSettingComponent &component, RulesComponent &rules)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Dot_01.png"),
        "Indie Studio",
        irr::core::vector2df(11.3, 56),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 55),
        irr::core::vector2df(20, 8)
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 55),
        irr::core::vector2df(7, 8)
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Max Time",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 55 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 13 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        true,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        rules.getTimeString(),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 55.3f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        rules.getTimeString(),
        "Indie Studio",
        1350, 480,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1200,
        550,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            if (rules.getMaxTime() - 5 >= 60) {
                rules.setMaxTime(rules.getMaxTime() - 5);
            }
            value.setText(rules.getTimeString());
            valueToChange.setText(rules.getTimeString());
        },
        false,
        RESSOURCE("ui/RuleSettings/Backward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Backward_BTN_pressed.png")
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1550,
        550,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            if (rules.getMaxTime() + 5 <= 3600) {
                rules.setMaxTime(rules.getMaxTime() + 5);
            }
            value.setText(rules.getTimeString());
            valueToChange.setText(rules.getTimeString());
        },
        false,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );
    component.addRule(
        // On select
        [&dot, &backward, &forward, &valueToChange](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
            valueToChange.setVisible(true);
        },
        // On exit
        [&dot, &backward, &forward, &valueToChange](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
            valueToChange.setVisible(false);
        },
        // On disappear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(false);
            secondTable.setVisible(false);
            title.setVisible(false);
            value.setVisible(false);
        },
        // On rule up
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y - 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y - 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y - 10));
            title.move(irr::core::vector2di(0, -105));
            value.move(irr::core::vector2di(0, -105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.move(irr::core::vector2di(0, 105));
            value.move(irr::core::vector2di(0, 105));
        },
        // On appear
        [&firstTable, &secondTable, &title, &value](){
            firstTable.setVisible(true);
            secondTable.setVisible(true);
            title.setVisible(true);
            value.setVisible(true);
        }
    );
    return (e);
}

// std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createModeFpsRule(is::components::RulesSettingComponent &component, RulesComponent &rules)
// {
//     std::shared_ptr<Entity> e = std::make_shared<Entity>();

//     TextureComponent &dot = e->addComponent<TextureComponent>(
//         e,
//         RESSOURCE("ui/RuleSettings/Dot_01.png"),
//         "Indie Studio",
//         irr::core::vector2df(11.3, 66),
//         irr::core::vector2df(3, 5),
//         false
//     );
//     TextureComponent &firstTable = e->addComponent<TextureComponent>(
//         e,
//         RESSOURCE("ui/RuleSettings/Table_01.png"),
//         "Indie Studio",
//         irr::core::vector2df(15, 65),
//         irr::core::vector2df(20, 8)
//     );
//     TextureComponent &secondTable = e->addComponent<TextureComponent>(
//         e,
//         RESSOURCE("ui/RuleSettings/Table_01.png"),
//         "Indie Studio",
//         irr::core::vector2df(36, 65),
//         irr::core::vector2df(7, 8)
//     );
//     TextComponent &title = e->addComponent<TextComponent>(
//         e,
//         "Mode fps",
//         "Indie Studio",
//         280, 620,
//         270, 200,
//         false,
//         true,
//         RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
//         irr::video::SColor(255, 227, 245, 244)
//     );
//     TextComponent &value = e->addComponent<TextComponent>(
//         e,
//         (rules.isFpsMode() ? "On" : "Off"),
//         "Indie Studio",
//         560, 620,
//         400, 200,
//         false,
//         true,
//         RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
//         irr::video::SColor(255, 227, 245, 244)
//     );
//     TextComponent &valueToChange = e->addComponent<TextComponent>(
//         e,
//         (rules.isFpsMode() ? "On" : "Off"),
//         "Indie Studio",
//         1350, 480,
//         100, 200,
//         false,
//         true,
//         RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
//         irr::video::SColor(255, 227, 245, 244),
//         false
//     );
//     ButtonComponent &backward = e->addComponent<ButtonComponent>(
//         e,
//         "",
//         "Indie Studio",
//         1200,
//         550,
//         60, 60,
//         [&value, &valueToChange, &rules](){
//             rules.setFpsMode(!rules.isFpsMode());
//             value.setText((rules.isFpsMode() ? "On" : "Off"));
//             valueToChange.setText((rules.isFpsMode() ? "On" : "Off"));
//         },
//         false,
//         RESSOURCE("ui/RuleSettings/Backward_BTN.png"),
//         RESSOURCE("ui/RuleSettings/Backward_BTN_pressed.png")
//     );
//     ButtonComponent &forward = e->addComponent<ButtonComponent>(
//         e,
//         "",
//         "Indie Studio",
//         1550,
//         550,
//         60, 60,
//         [&value, &valueToChange, &rules](){
//             rules.setFpsMode(!rules.isFpsMode());
//             value.setText((rules.isFpsMode() ? "On" : "Off"));
//             valueToChange.setText((rules.isFpsMode() ? "On" : "Off"));
//         },
//         false,
//         RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
//         RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
//     );
//     component.addRule(
//         // On select
//         [&dot, &backward, &forward, &valueToChange](){
//             dot.setVisible(true);
//             backward.setVisible(true);
//             forward.setVisible(true);
//             valueToChange.setVisible(true);
//         },
//         // On exit
//         [&dot, &backward, &forward, &valueToChange](){
//             dot.setVisible(false);
//             backward.setVisible(false);
//             forward.setVisible(false);
//             valueToChange.setVisible(false);
//         },
//         // On disappear
//         [&firstTable, &secondTable, &title, &value](){
//             firstTable.setVisible(false);
//             secondTable.setVisible(false);
//             title.setVisible(false);
//             value.setVisible(false);
//         },
//         // On rule up
//         [&dot, &firstTable, &secondTable, &title, &value](){
//             dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y - 10));
//             firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y - 10));
//             secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y - 10));
//             title.move(irr::core::vector2di(0, -105));
//             value.move(irr::core::vector2di(0, -105));
//         },
//         // On rule down
//         [&dot, &firstTable, &secondTable, &title, &value](){
//             dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
//             firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
//             secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
//             title.move(irr::core::vector2di(0, 105));
//             value.move(irr::core::vector2di(0, 105));
//         },
//         // On appear
//         [&firstTable, &secondTable, &title, &value](){
//             firstTable.setVisible(true);
//             secondTable.setVisible(true);
//             title.setVisible(true);
//             value.setVisible(true);
//         }
//     );
//     return (e);
// }