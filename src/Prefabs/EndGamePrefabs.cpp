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

using namespace is::ecs;
using namespace is::components;

std::shared_ptr<Entity> is::prefabs::EndGamePrefabs::createBackground()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio",
        irr::core::vector2df(0, -1),
        irr::core::vector2df(100, 120)
    );
    return (e);
}

std::shared_ptr<::Entity> is::prefabs::EndGamePrefabs::createPlayer(std::vector<std::pair<std::string, std::string>> &infos, bool isAI, const std::string &texture)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 18),
        irr::core::vector3df(0, -120, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio", RESSOURCE(texture));
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    addWindow(e, 2.5);
    addStatsPlayer(e, addTextHigh(e, 102), addTextLow(e, 102), infos);
    addContinueButton(e, 80, addWaitingText(e, 140), isAI);
    addHighTable(e, 3.5);
    addLowTable(e, 3.5);
    addMedal(e, 10, "ui/EndGame/Star_01.png");
    addBackwardButton(e, 100);
    addForwardButton(e, 340);
    return (e);
}

std::shared_ptr<::Entity> is::prefabs::EndGamePrefabs::createPlayer2(std::vector<std::pair<std::string, std::string>> &infos, bool isAI, const std::string &texture)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 6),
        irr::core::vector3df(0, -100, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio", RESSOURCE(texture));
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    addWindow(e, 26.3);
    addStatsPlayer(e, addTextHigh(e, 565), addTextLow(e, 565), infos);
    addContinueButton(e, 540, addWaitingText(e, 600), isAI);
    addHighTable(e, 27.2);
    addLowTable(e, 27.2);
    addMedal(e, 34, "ui/EndGame/Star_02.png");
    addBackwardButton(e, 560);
    addForwardButton(e, 800);
    return (e);
}

std::shared_ptr<::Entity> is::prefabs::EndGamePrefabs::createPlayer3(std::vector<std::pair<std::string, std::string>> &infos, bool isAI, const std::string &texture)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -6),
        irr::core::vector3df(0, -70, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio", RESSOURCE(texture));
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    addWindow(e, 51.3);
    addStatsPlayer(e, addTextHigh(e, 1045), addTextLow(e, 1045), infos);
    addContinueButton(e, 1020, addWaitingText(e, 1080), isAI);
    addHighTable(e, 52.2);
    addLowTable(e, 52.2);
    addMedal(e, 58, "ui/EndGame/Star_03.png");
    addBackwardButton(e, 1040);
    addForwardButton(e, 1280);
    return (e);
}

std::shared_ptr<::Entity> is::prefabs::EndGamePrefabs::createPlayer4(std::vector<std::pair<std::string, std::string>> &infos, bool isAI, const std::string &texture)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -19),
        irr::core::vector3df(0, -50, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio", RESSOURCE(texture));
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    addWindow(e, 76.3);
    addStatsPlayer(e, addTextHigh(e, 1525), addTextLow(e, 1525), infos);
    addContinueButton(e, 1500, addWaitingText(e, 1560), isAI);
    addHighTable(e, 77.2);
    addLowTable(e, 77.2);
    addBackwardButton(e, 1520);
    addForwardButton(e, 1760);
    return (e);
}


// * PRIVATE METHOD

void is::prefabs::EndGamePrefabs::addStatsPlayer(
    std::shared_ptr<::Entity> &e,
    TextComponent &textHigh,
    TextComponent &textLow,
    std::vector<std::pair<std::string, std::string>> &infos
)
{
    textHigh.setText((infos.size() > 0 ? infos[0].first : ""));
    textLow.setText((infos.size() > 0 ? infos[0].second : ""));
    e->addComponent<StatsComponent>(
        e,
        textHigh,
        textLow,
        infos
    );
}

void is::prefabs::EndGamePrefabs::addWindow(std::shared_ptr<::Entity> &e, double posX)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table_01.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 10),
        irr::core::vector2df(21.85, 80)
    );
}

void is::prefabs::EndGamePrefabs::addContinueButton(std::shared_ptr<::Entity> &e, int posX, TextComponent &text, bool isAI)
{
    if (isAI) {
        text.setText("Waiting...");
        e->getComponent<StatsComponent>().value()->setContinue(true);
        return;
    }
    ButtonComponent &button = e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX + 75,
        850,
        200, 60,
        [](){},
        true,
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    button.setCallback([&button, &text, e]() {
        button.deleteComponent();
        text.setText("Waiting...");
        e->getComponent<StatsComponent>().value()->setContinue(true);
    });
}

void is::prefabs::EndGamePrefabs::addBackwardButton(std::shared_ptr<::Entity> &e, int posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX,
        750,
        70, 70,
        [e](){
            e->getComponent<StatsComponent>().value()->prev();
        },
        true,
        RESSOURCE("ui/EndGame/Backward_BTN.png"),
        RESSOURCE("ui/EndGame/Backward_BTN_pressed.png")
    );
}

void is::prefabs::EndGamePrefabs::addForwardButton(std::shared_ptr<::Entity> &e, int posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        posX,
        750,
        70, 70,
        [e](){
            e->getComponent<StatsComponent>().value()->next();
        },
        true,
        RESSOURCE("ui/EndGame/Forward_BTN.png"),
        RESSOURCE("ui/EndGame/Forward_BTN_pressed.png")
    );
}

void is::prefabs::EndGamePrefabs::addHighTable(std::shared_ptr<::Entity> &e, double posX)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 50),
        irr::core::vector2df(19.8, 10)
    );
}

void is::prefabs::EndGamePrefabs::addLowTable(std::shared_ptr<::Entity> &e, double posX)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Table.png"),
        "Indie Studio",
        irr::core::vector2df(posX, 60),
        irr::core::vector2df(19.8, 10)
    );
}

void is::prefabs::EndGamePrefabs::addMedal(std::shared_ptr<::Entity> &e, double posX, const std::string &filename)
{
    e->addComponent<TextureComponent>(
        e,
        RESSOURCE(filename),
        "Indie Studio",
        irr::core::vector2df(posX, 12),
        irr::core::vector2df(7, 10)
    );
}

TextComponent &is::prefabs::EndGamePrefabs::addTextHigh(std::shared_ptr<::Entity> &e, int posX)
{
    return e->addComponent<TextComponent>(
        e,
        "Number of players killed",
        "Indie Studio",
        posX, 472,
        300, 200,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}

TextComponent &is::prefabs::EndGamePrefabs::addTextLow(std::shared_ptr<::Entity> &e, int posX)
{
    return e->addComponent<TextComponent>(
        e,
        "6",
        "Indie Studio",
        posX, 580,
        300, 200,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}

TextComponent &is::prefabs::EndGamePrefabs::addWaitingText(std::shared_ptr<::Entity> &e, int posX)
{
    return e->addComponent<TextComponent>(
        e,
        "",
        "Indie Studio",
        posX, 530,
        250, 700,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}