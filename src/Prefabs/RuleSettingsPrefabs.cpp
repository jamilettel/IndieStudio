/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#include "Prefabs/RuleSettingsPrefabs.hpp"

using namespace is::ecs;
using namespace is::prefabs;
using namespace is::exceptions;
using namespace is::components;

std::shared_ptr<Entity> RuleSettingsPrefabs::createBackground()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TextureComponent>(
        e,
        "ui/background.jpg",
        "Indie Studio",
        irr::core::vector2df(0, -1),
        irr::core::vector2df(100, 120)
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createOkButton(const std::shared_ptr<NetworkComponent> &nc, RulesComponent &rules)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 85 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 12 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        [nc, &rules]() {
            nc->writeQueue.push("req cl " + std::to_string(rules.getNumberOfPlayers()) + " " + std::to_string(rules.getMaxTime()) + " \n");
        },
        true,
        "ui/RuleSettings/OkButton.png",
        "ui/RuleSettings/OkButtonPressed.png"
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createReturnButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
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
        "ui/RuleSettings/Return_BTN.png",
        "ui/RuleSettings/Return_BTN_pressed.png"
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createRuleSettings()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<RulesSettingComponent>(e);
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createSettingsBackground(RulesSettingComponent &component)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table.png",
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
        "ui/RuleSettings/Upward_BTN.png",
        "ui/RuleSettings/Upward_BTN_pressed.png"
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
        "ui/RuleSettings/Downward_BTN.png",
        "ui/RuleSettings/Downward_BTN_pressed.png"
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createNumberOfPlayersRule(RulesSettingComponent &component, RulesComponent &rules, int pos, bool visible)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Dot_01.png",
        "Indie Studio",
        irr::core::vector2df(11.3, pos + 1),
        irr::core::vector2df(3, 5)
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(15, pos),
        irr::core::vector2df(20, 8),
        visible
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(36, pos),
        irr::core::vector2df(7, 8),
        visible
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Number of players",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * pos / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 20 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getNumberOfPlayers()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * (pos + 0.3f) / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getNumberOfPlayers()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 72.5f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 68 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
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
        "ui/RuleSettings/Backward_BTN.png",
        "ui/RuleSettings/Backward_BTN_pressed.png"
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 82 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
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
        "ui/RuleSettings/Forward_BTN.png",
        "ui/RuleSettings/Forward_BTN_pressed.png"
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
        },
        // On reset
        [&value, &valueToChange, &rules](){
            value.setText(std::to_string(rules.getNumberOfPlayers()));
            valueToChange.setText(std::to_string(rules.getNumberOfPlayers()));
        }
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createIconsRule(RulesSettingComponent &component, RulesComponent &rules, int pos, bool visible)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Dot_01.png",
        "Indie Studio",
        irr::core::vector2df(11.3, pos + 1),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(15, pos),
        irr::core::vector2df(20, 8),
        visible
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(36, pos),
        irr::core::vector2df(7, 8),
        visible
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Icons",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * pos / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        (rules.noIconUsed() ? "Off" : "On"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * (pos + 0.3f) / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        (rules.noIconUsed() ? "Off" : "On"),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 71 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 33 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    TextureComponent &onOff = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(71, 33),
        irr::core::vector2df(7, 8),
        false
    );
    TextureComponent &highBox = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Box.png",
        "Indie Studio",
        irr::core::vector2df(60, 45),
        irr::core::vector2df(30, 25),
        false
    );

    ButtonComponent &acceleratorDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 62 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/disable.png",
        "ui/RuleSettings/disable.png"
    );
    acceleratorDisable.layer = 1;
    ButtonComponent &accelerator = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 62 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/accelerator.png",
        "ui/RuleSettings/accelerator.png"
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
    if (!rules.useIcon(rules.ACCELERATOR)) {
        accelerator.setDisabled(true);
    } else {
        acceleratorDisable.setDisabled(true);
    }

    ButtonComponent &bombDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 66 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/disable.png",
        "ui/RuleSettings/disable.png"
    );
    bombDisable.layer = 1;
    ButtonComponent &bomb = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 66 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/bomb.png",
        "ui/RuleSettings/bomb.png"
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
    if (!rules.useIcon(rules.BOMB)) {
        bomb.setDisabled(true);
    } else {
        bombDisable.setDisabled(true);
    }

    ButtonComponent &explosionDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 70 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/disable.png",
        "ui/RuleSettings/disable.png"
    );
    explosionDisable.layer = 1;
    ButtonComponent &explosion = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 70 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/explosion_expander.png",
        "ui/RuleSettings/explosion_expander.png"
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
    if (!rules.useIcon(rules.EXPLOSION)) {
        explosion.setDisabled(true);
    } else {
        explosionDisable.setDisabled(true);
    }

    ButtonComponent &wallPassDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 74 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/disable.png",
        "ui/RuleSettings/disable.png"
    );
    wallPassDisable.layer = 1;
    ButtonComponent &wallPass = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 74 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        false,
        "ui/RuleSettings/wall_pass.png",
        "ui/RuleSettings/wall_pass.png"
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
    if (!rules.useIcon(rules.WALL_PASS)) {
        wallPass.setDisabled(true);
    } else {
        wallPassDisable.setDisabled(true);
    }

    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 66 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 34 / 100,
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
        "ui/RuleSettings/Backward_BTN.png",
        "ui/RuleSettings/Backward_BTN_pressed.png"
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 80 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 34 / 100,
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
        "ui/RuleSettings/Forward_BTN.png",
        "ui/RuleSettings/Forward_BTN_pressed.png"
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
        },
        // On reset
        [&value, &valueToChange, &rules, &wallPassDisable, &acceleratorDisable, &bombDisable, &explosionDisable](){
            value.setText("On");
            valueToChange.setText("On");
            wallPassDisable.setClicked(true);
            acceleratorDisable.setClicked(true);
            bombDisable.setClicked(true);
            explosionDisable.setClicked(true);
        }
    );
    return (e);
}

std::shared_ptr<Entity> RuleSettingsPrefabs::createMaxTimeRule(RulesSettingComponent &component, RulesComponent &rules, int pos, bool visible)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Dot_01.png",
        "Indie Studio",
        irr::core::vector2df(11.3, pos + 1),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(15, pos),
        irr::core::vector2df(20, 8),
        visible
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(36, pos),
        irr::core::vector2df(7, 8),
        visible
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Max Time",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * pos / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 13 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        rules.getTimeString(),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * (pos + 0.3f) / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        rules.getTimeString(),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 72.5f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 67 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
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
        "ui/RuleSettings/Backward_BTN.png",
        "ui/RuleSettings/Backward_BTN_pressed.png"
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 82 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
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
        "ui/RuleSettings/Forward_BTN.png",
        "ui/RuleSettings/Forward_BTN_pressed.png"
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
        },
        // On reset
        [&value, &valueToChange, &rules](){
            value.setText(rules.getTimeString());
            valueToChange.setText(rules.getTimeString());
        }
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createSeedRule(is::components::RulesSettingComponent &component, RulesComponent &rules, int pos, bool visible)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Dot_01.png",
        "Indie Studio",
        irr::core::vector2df(11.3, pos + 1),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(15, pos),
        irr::core::vector2df(20, 8),
        visible
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(36, pos),
        irr::core::vector2df(7, 8),
        visible
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Seed",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * pos / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 9 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getSeed()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * (pos + 0.3f) / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getSeed()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 72.5f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 67 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            rules.decSeed();
            value.setText(std::to_string(rules.getSeed()));
            valueToChange.setText(std::to_string(rules.getSeed()));
        },
        false,
        "ui/RuleSettings/Backward_BTN.png",
        "ui/RuleSettings/Backward_BTN_pressed.png"
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 82 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            rules.incSeed();
            value.setText(std::to_string(rules.getSeed()));
            valueToChange.setText(std::to_string(rules.getSeed()));
        },
        false,
        "ui/RuleSettings/Forward_BTN.png",
        "ui/RuleSettings/Forward_BTN_pressed.png"
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
        },
        // On reset
        [&value, &valueToChange, &rules](){
            value.setText(std::to_string(rules.getSeed()));
            valueToChange.setText(std::to_string(rules.getSeed()));
        }
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createPowerupFrequency(RulesSettingComponent &component, RulesComponent &rules, int pos, bool visible)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Dot_01.png",
        "Indie Studio",
        irr::core::vector2df(11.3, pos + 1),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(15, pos),
        irr::core::vector2df(20, 8),
        visible
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        "ui/RuleSettings/Table_01.png",
        "Indie Studio",
        irr::core::vector2df(36, pos),
        irr::core::vector2df(7, 8),
        visible
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Powerup rate",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15.5 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * pos / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getPowerupFrequency()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 36 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * (pos + 0.3f) / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        visible
    );
    TextComponent &valueToChange = e->addComponent<TextComponent>(
        e,
        std::to_string(rules.getPowerupFrequency()),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 72.5f / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 49 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 7 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244),
        false
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 67 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            rules.decPowerupFrequency();
            value.setText(std::to_string(rules.getPowerupFrequency()));
            valueToChange.setText(std::to_string(rules.getPowerupFrequency()));
        },
        false,
        "ui/RuleSettings/Backward_BTN.png",
        "ui/RuleSettings/Backward_BTN_pressed.png"
    );
    ButtonComponent &forward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * 82 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [&value, &valueToChange, &rules](){
            rules.incPowerupFrequency();
            value.setText(std::to_string(rules.getPowerupFrequency()));
            valueToChange.setText(std::to_string(rules.getPowerupFrequency()));
        },
        false,
        "ui/RuleSettings/Forward_BTN.png",
        "ui/RuleSettings/Forward_BTN_pressed.png"
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
        },
        // On reset
        [&value, &valueToChange, &rules](){
            value.setText(std::to_string(rules.getPowerupFrequency()));
            valueToChange.setText(std::to_string(rules.getPowerupFrequency()));
        }
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createDefaultButton(
    is::components::RulesSettingComponent &component,
    is::components::RulesComponent &rules,
    float posX,
    float posY
)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].second * posY / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 12 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 7 / 100,
        [&component, &rules]() {
            rules.reset();
            component.reset();
        },
        true,
        "ui/RuleSettings/defaultButton.png",
        "ui/RuleSettings/defaultButtonPressed.png"
    );
    return (e);
}