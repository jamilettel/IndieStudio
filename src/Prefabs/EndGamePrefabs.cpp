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

std::shared_ptr<::Entity> is::prefabs::EndGamePrefabs::createPlayer(
    std::vector<std::pair<std::string, std::string>> &infos,
    bool isAI, 
    const std::string &texture,
    float posWindow,
    std::pair<float, float> &posModelPlayer,
    int position
)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, posModelPlayer.first),
        irr::core::vector3df(0, posModelPlayer.second, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio", RESSOURCE(texture));
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    addWindow(e, posWindow);
    addStatsPlayer(e, addTextHigh(e, posWindow + 3.2f), addTextLow(e, posWindow + 3.2f), infos);
    addContinueButton(e, posWindow + 5.7f, addWaitingText(e, posWindow + 4.7f), isAI);
    addHighTable(e, posWindow + 1);
    addLowTable(e, posWindow + 1);
    switch (position)
    {
    case 1:
        addMedal(e, posWindow + 7.5, "ui/EndGame/Star_03.png");
        break;
    case 2:
        addMedal(e, posWindow + 7.5, "ui/EndGame/Star_02.png");
        break;
    case 3:
        addMedal(e, posWindow + 7.5, "ui/EndGame/Star_01.png");
        break;
    }
    addBackwardButton(e, posWindow + 2.5);
    addForwardButton(e, posWindow + 16.5);
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

void is::prefabs::EndGamePrefabs::addContinueButton(std::shared_ptr<::Entity> &e, float posX, TextComponent &text, bool isAI)
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
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 81 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 10 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [](){},
        true,
        RESSOURCE("ui/EndGame/continue_button.png"),
        RESSOURCE("ui/EndGame/continue_button_pressed.png")
    );
    button.layer = 1;
    button.setCallback([&button, &text, e]() {
        button.deleteComponent();
        text.setText("Waiting...");
        e->getComponent<StatsComponent>().value()->setContinue(true);
    });
}

void is::prefabs::EndGamePrefabs::addBackwardButton(std::shared_ptr<::Entity> &e, float posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 71 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
        [e](){
            e->getComponent<StatsComponent>().value()->prev();
        },
        true,
        RESSOURCE("ui/EndGame/Backward_BTN.png"),
        RESSOURCE("ui/EndGame/Backward_BTN_pressed.png")
    );
}

void is::prefabs::EndGamePrefabs::addForwardButton(std::shared_ptr<::Entity> &e, float posX)
{
    e->addComponent<ButtonComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 71 / 100,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 2.7f / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 5 / 100,
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

TextComponent &is::prefabs::EndGamePrefabs::addTextHigh(std::shared_ptr<::Entity> &e, float posX)
{
    return e->addComponent<TextComponent>(
        e,
        "Number of players killed",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 50 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 9 / 100,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}

TextComponent &is::prefabs::EndGamePrefabs::addTextLow(std::shared_ptr<::Entity> &e, float posX)
{
    return e->addComponent<TextComponent>(
        e,
        "6",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 60 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 15 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 9 / 100,
        false,
        true,
        RESSOURCE("fonts/EndGame/endGameFont.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}

TextComponent &is::prefabs::EndGamePrefabs::addWaitingText(std::shared_ptr<::Entity> &e, float posX)
{
    return e->addComponent<TextComponent>(
        e,
        "",
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first * posX / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 79 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].first * 12 / 100.0f,
        WindowComponent::_windowsDimensions["Indie Studio"].second * 9 / 100,
        false,
        true,
        RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml"),
        irr::video::SColor(255, 227, 245, 244)
    );
}