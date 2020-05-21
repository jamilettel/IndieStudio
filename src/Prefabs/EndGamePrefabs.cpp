/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndGamePrefabs
*/

#include "Prefabs/EndGamePrefabs.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::components;
using namespace is::ecs;

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createBackground()
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

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 18),
        irr::core::vector3df(0, -120, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer2()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 6),
        irr::core::vector3df(0, -100, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer3()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -6),
        irr::core::vector3df(0, -70, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer4()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -19),
        irr::core::vector3df(0, -50, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(2.5, 10),
        irr::core::vector2df(21.9, 80)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow2()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(26.3, 10),
        irr::core::vector2df(21.85, 80)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow3()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(51.3, 10),
        irr::core::vector2df(21.85, 80)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow4()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(76.3, 10),
        irr::core::vector2df(21.85, 80)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createContinueButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        40,
        750,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createContinueButton2()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        420,
        750,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createContinueButton3()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        820,
        750,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createContinueButton4()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        1220,
        750,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createBackwardButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        80,
        650,
        70, 70,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/Backward_BTN.png"),
        RESSOURCE("ui/EndGame/Backward_BTN.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createForwardButton()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        280,
        650,
        70, 70,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/Forward_BTN.png"),
        RESSOURCE("ui/EndGame/Forward_BTN.png")
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createText()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TextComponent>(
        e,
        "Number player killed",
        "Indie Studio",
        is::components::WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 1050 / 2,
        300,
        1000, 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 255, 255, 255)
    );
    return (e);
}