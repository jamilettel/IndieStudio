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