/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#include "Prefabs/RuleSettingsPrefabs.hpp"

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
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 35),
        irr::core::vector2df(20, 8)
    );
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 35),
        irr::core::vector2df(7, 8)
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
        [&dot, &backward, &forward](){
            dot.setVisible(true);
            backward.setVisible(true);
            forward.setVisible(true);
        },
        [&dot, &backward, &forward](){
            dot.setVisible(false);
            backward.setVisible(false);
            forward.setVisible(false);
        });
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
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 45),
        irr::core::vector2df(20, 8)
    );
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 45),
        irr::core::vector2df(7, 8)
    );
    component.addRule(
        [&dot](){
            dot.setVisible(true);
        },
        [&dot](){
            dot.setVisible(false);
        });
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
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 55),
        irr::core::vector2df(20, 8)
    );
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 55),
        irr::core::vector2df(7, 8)
    );
    component.addRule(
        [&dot](){
            dot.setVisible(true);
        },
        [&dot](){
            dot.setVisible(false);
        });
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
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(15, 65),
        irr::core::vector2df(20, 8)
    );
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/RuleSettings/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(36, 65),
        irr::core::vector2df(7, 8)
    );
    component.addRule(
        [&dot](){
            dot.setVisible(true);
        },
        [&dot](){
            dot.setVisible(false);
        });
    return (e);
}
