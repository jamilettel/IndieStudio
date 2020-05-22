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
    addWindow(e, 2.5);
    addContinueButton(e, 40);
    addBackwardButton(e, 80);
    addForwardButton(e, 280);
    addHighTable(e, 3.5);
    addLowTable(e, 3.5);
    addMedal(e, 10, "ui/EndGame/Star_01.png");
    addTextHigh(e, 62);
    addTextLow(e, 62);
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
    addWindow(e, 26.3);
    addContinueButton(e, 420);
    addBackwardButton(e, 450);
    addForwardButton(e, 670);
    addHighTable(e, 27.2);
    addLowTable(e, 27.2);
    addMedal(e, 34, "ui/EndGame/Star_01.png");
    addTextHigh(e, 445);
    addTextLow(e, 445);
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
    addWindow(e, 51.3);
    addContinueButton(e, 820);
    addBackwardButton(e, 850);
    addForwardButton(e, 1070);
    addHighTable(e, 52.2);
    addLowTable(e, 52.2);
    addMedal(e, 58, "ui/EndGame/Star_01.png");
    addTextHigh(e, 845);
    addTextLow(e, 845);
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
    addWindow(e, 76.3);
    addContinueButton(e, 1220);
    addBackwardButton(e, 1250);
    addForwardButton(e, 1470);
    addHighTable(e, 77.2);
    addLowTable(e, 77.2);
    // addMedal(e, 58, RESSOURCE("ui/EndGame/Star_01.png"));
    addTextHigh(e, 1245);
    addTextLow(e, 1245);
    return (e);
}


// * PRIVATE METHOD

void is::prefabs::EndGamePrefabs::addWindow(std::shared_ptr<is::ecs::Entity> &e, double posX)
{
    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 10),
        irr::core::vector2df(21.85, 80)
    );
}

void is::prefabs::EndGamePrefabs::addContinueButton(std::shared_ptr<is::ecs::Entity> &e, int posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX,
        750,
        350, 100,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
}

void is::prefabs::EndGamePrefabs::addBackwardButton(std::shared_ptr<is::ecs::Entity> &e, int posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX,
        650,
        70, 70,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/Backward_BTN.png"),
        RESSOURCE("ui/EndGame/Backward_BTN.png")
    );
}

void is::prefabs::EndGamePrefabs::addForwardButton(std::shared_ptr<is::ecs::Entity> &e, int posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX,
        650,
        70, 70,
        [](){
            is::Game::setActualScene(is::ecs::SCENE_PRESETSELECTION);
        },
        RESSOURCE("ui/EndGame/Forward_BTN.png"),
        RESSOURCE("ui/EndGame/Forward_BTN.png")
    );
}

void is::prefabs::EndGamePrefabs::addHighTable(std::shared_ptr<is::ecs::Entity> &e, double posX)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 50),
        irr::core::vector2df(19.8, 10)
    );
}

void is::prefabs::EndGamePrefabs::addLowTable(std::shared_ptr<is::ecs::Entity> &e, double posX)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 60),
        irr::core::vector2df(19.8, 10)
    );
}

void is::prefabs::EndGamePrefabs::addMedal(std::shared_ptr<is::ecs::Entity> &e, double posX, const std::string &filename)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE(filename),
        "Indie Studio",
        irr::core::vector2df(posX, 12),
        irr::core::vector2df(7, 10)
    );
}

void is::prefabs::EndGamePrefabs::addTextHigh(std::shared_ptr<is::ecs::Entity> &e, int posX)
{
    e->addComponent<TextComponent>(
        e,
        "Number of players killed",
        "Indie Studio",
        posX, 390,
        300, 200,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
    // 62
}

void is::prefabs::EndGamePrefabs::addTextLow(std::shared_ptr<is::ecs::Entity> &e, int posX)
{
    e->addComponent<TextComponent>(
        e,
        "6",
        "Indie Studio",
        posX, 480,
        300, 200,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}