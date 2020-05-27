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

std::shared_ptr<is::ecs::Entity>  RuleSettingsPrefabs::createSaveButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1600,
        60,
        250, 80,
        [](){},
        true,
        RESSOURCE("ui/RuleSettings/button_save.png"),
        RESSOURCE("ui/RuleSettings/button_save_pressed.png")
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
        60,
        60,
        60, 60,
        [](){},
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
        500,
        250,
        60, 60,
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
        500,
        850,
        60, 60,
        [&component](){
            component.up();
        },
        true,
        RESSOURCE("ui/RuleSettings/Downward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Downward_BTN_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createNumberOfPlayersRule(is::components::RulesSettingComponent &component)
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
        280, 305,
        400, 200,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        "4",
        "Indie Studio",
        560, 305,
        400, 200,
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
        60, 60,
        [](){},
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
        60, 60,
        [](){},
        true,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );
    component.addRule(
        // On select
        [&dot, &backward, &forward](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
        },
        // On exit
        [&dot, &backward, &forward](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
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
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y - 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y - 105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y + 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y + 105));
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

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createIconsRule(is::components::RulesSettingComponent &component)
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
        280, 410,
        190, 200,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        "On",
        "Indie Studio",
        560, 410,
        400, 200,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    ButtonComponent &backward = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1250,
        360,
        60, 60,
        [](){},
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
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
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
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    acceleratorDisable.setDisabled(true);
    ButtonComponent &accelerator = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1200,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/accelerator.png"),
        RESSOURCE("ui/RuleSettings/accelerator.png")
    );
    accelerator.setCallback([&accelerator, &acceleratorDisable](){
        accelerator.setDisabled(true);
        acceleratorDisable.setDisabled(false);
        acceleratorDisable.setVisible(true);
    });
    acceleratorDisable.setCallback([&accelerator, &acceleratorDisable](){
        accelerator.setDisabled(false);
        acceleratorDisable.setDisabled(true);
        acceleratorDisable.setVisible(false);
    });

    ButtonComponent &bombDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1270,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    bombDisable.setDisabled(true);
    ButtonComponent &bomb = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1270,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/bomb.png"),
        RESSOURCE("ui/RuleSettings/bomb.png")
    );
    bomb.setCallback([&bomb, &bombDisable](){
        bomb.setDisabled(true);
        bombDisable.setDisabled(false);
        bombDisable.setVisible(true);
    });
    bombDisable.setCallback([&bomb, &bombDisable](){
        bomb.setDisabled(false);
        bombDisable.setDisabled(true);
        bombDisable.setVisible(false);
    });

    ButtonComponent &explosionDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1340,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    explosionDisable.setDisabled(true);
    ButtonComponent &explosion = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1340,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/explosion_expander.png"),
        RESSOURCE("ui/RuleSettings/explosion_expander.png")
    );
    explosion.setCallback([&explosion, &explosionDisable](){
        explosion.setDisabled(true);
        explosionDisable.setDisabled(false);
        explosionDisable.setVisible(true);
    });
    explosionDisable.setCallback([&explosion, &explosionDisable](){
        explosion.setDisabled(false);
        explosionDisable.setDisabled(true);
        explosionDisable.setVisible(false);
    });

    ButtonComponent &wallPassDisable = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1410,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/disable.png"),
        RESSOURCE("ui/RuleSettings/disable.png")
    );
    wallPassDisable.setDisabled(true);
    ButtonComponent &wallPass = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1410,
        510,
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/wall_pass.png"),
        RESSOURCE("ui/RuleSettings/wall_pass.png")
    );
    wallPass.setCallback([&wallPass, &wallPassDisable](){
        wallPass.setDisabled(true);
        wallPassDisable.setDisabled(false);
        wallPassDisable.setVisible(true);
    });
    wallPassDisable.setCallback([&wallPass, &wallPassDisable](){
        wallPass.setDisabled(false);
        wallPassDisable.setDisabled(true);
        wallPassDisable.setVisible(false);
    });

    component.addRule(
        // On select
        [&dot, &forward, &backward, &onOff, &highBox, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable](){
            dot.setVisible(true);
            forward.setVisible(true);
            backward.setVisible(true);
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
        [&dot, &forward, &backward, &onOff, &highBox, &accelerator, &bomb, &explosion, &wallPass, &acceleratorDisable, &bombDisable, &explosionDisable, &wallPassDisable](){
            dot.setVisible(false);
            forward.setVisible(false);
            backward.setVisible(false);
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
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y - 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y - 105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y + 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y + 105));
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

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createMaxTimeRule(is::components::RulesSettingComponent &component)
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
        280, 515,
        270, 200,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        "03:00",
        "Indie Studio",
        560, 515,
        400, 200,
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
        60, 60,
        [](){},
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
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );
    component.addRule(
        // On select
        [&dot, &backward, &forward](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
        },
        // On exit
        [&dot, &backward, &forward](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
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
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y - 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y - 105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y + 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y + 105));
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

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createModeFpsRule(is::components::RulesSettingComponent &component)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Dot_01.png"),
        "Indie Studio",
        irr::core::vector2df(11.3, 66),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 65),
        irr::core::vector2df(20, 8)
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 65),
        irr::core::vector2df(7, 8)
    );
    TextComponent &title = e->addComponent<TextComponent>(
        e,
        "Mode fps",
        "Indie Studio",
        280, 620,
        270, 200,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    TextComponent &value = e->addComponent<TextComponent>(
        e,
        "Off",
        "Indie Studio",
        560, 620,
        400, 200,
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
        60, 60,
        [](){},
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
        60, 60,
        [](){},
        false,
        RESSOURCE("ui/RuleSettings/Forward_BTN.png"),
        RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")
    );
    component.addRule(
        // On select
        [&dot, &backward, &forward](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
        },
        // On exit
        [&dot, &backward, &forward](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
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
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y - 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y - 105));
        },
        // On rule down
        [&dot, &firstTable, &secondTable, &title, &value](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
            title.setPosition(irr::core::vector2di(title.getPosition().X, title.getPosition().Y + 105));
            value.setPosition(irr::core::vector2di(value.getPosition().X, value.getPosition().Y + 105));
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

std::shared_ptr<is::ecs::Entity> RuleSettingsPrefabs::createEmptyRule(is::components::RulesSettingComponent &component)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    TextureComponent &dot = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Dot_01.png"),
        "Indie Studio",
        irr::core::vector2df(11.3, 76),
        irr::core::vector2df(3, 5),
        false
    );
    TextureComponent &firstTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 75),
        irr::core::vector2df(20, 8),
        false
    );
    TextureComponent &secondTable = e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 75),
        irr::core::vector2df(7, 8),
        false
    );

    component.addRule(
        // On select
        [&dot](){
            dot.setVisible(true);
        },
        // on exit
        [&dot](){
            dot.setVisible(false);
        },
        // On disappear
        [&firstTable, &secondTable](){
            firstTable.setVisible(false);
            secondTable.setVisible(false);
        },
        // On rule up
        [&dot, &firstTable, &secondTable](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y - 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y - 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y - 10));
        },
        // On rule down
        [&dot, &firstTable, &secondTable](){
            dot.setPosition(irr::core::vector2df(dot.getPosition().X, dot.getPosition().Y + 10));
            firstTable.setPosition(irr::core::vector2df(firstTable.getPosition().X, firstTable.getPosition().Y + 10));
            secondTable.setPosition(irr::core::vector2df(secondTable.getPosition().X, secondTable.getPosition().Y + 10));
        },
        // On appear
        [&firstTable, &secondTable](){
            firstTable.setVisible(true);
            secondTable.setVisible(true);
        }
    );
    return (e);
}