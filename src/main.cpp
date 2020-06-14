/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Exception.hpp"
#include <iostream>

int bomberman(int argc, char const *argv[])
{
    is::Game game;

    try {
#ifdef _WIN32
        WSADATA data;

        if (!SetProcessDPIAware())
            throw is::exceptions::WindowException("SetProcessDPIAware failed.");
        WSAStartup(MAKEWORD(2, 2), &data);
#endif
        game.addScene(is::ecs::Scenes::SCENE_SPLASH_SCREEN, std::make_shared<is::scenes::SplashScreenScene>());
        game.addScene(is::ecs::Scenes::SCENE_MAIN_MENU, std::make_shared<is::scenes::MainMenuScene>());
        game.addScene(is::ecs::Scenes::SCENE_CREDIT, std::make_shared<is::scenes::CreditScene>());
        game.addScene(is::ecs::Scenes::SCENE_HOWTOPLAY, std::make_shared<is::scenes::HowToPlayScene>());
        game.addScene(is::ecs::Scenes::SCENE_PAUSE, std::make_shared<is::scenes::PauseScene>());
        game.addScene(is::ecs::Scenes::SCENE_GAME, std::make_shared<is::scenes::GameScene>());
        game.addScene(is::ecs::Scenes::SCENE_SETTINGS, std::make_shared<is::scenes::SettingsScene>());
        game.addScene(is::ecs::Scenes::SCENE_CONTROLLERS, std::make_shared<is::scenes::ControllersScene>());
        game.addScene(is::ecs::Scenes::SCENE_PRESETSELECTION, std::make_shared<is::scenes::PresetSelectionScene>());
        game.addScene(is::ecs::Scenes::SCENE_MULTIPLAYER_HUB, std::make_shared<is::scenes::MultiplayerHubScene>());
        game.addScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY_CHOICE, std::make_shared<is::scenes::MultiplayerLobbyChoiceScene>());
        game.addScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY, std::make_shared<is::scenes::MultiplayerLobbyScene>());
        game.addScene(is::ecs::Scenes::SCENE_MULTIPLAYER_GAME, std::make_shared<is::scenes::MultiplayerGameScene>());
        game.addScene(is::ecs::Scenes::SCENE_ENDGAME, std::make_shared<is::scenes::EndGameScene>());
        game.addScene(is::ecs::Scenes::SCENE_RULE_SETTINGS, std::make_shared<is::scenes::RuleSettingsScene>());
        game.addScene(is::ecs::Scenes::SCENE_MULTIPLAYER_RULE_SETTINGS, std::make_shared<is::scenes::MultiplayerRuleSettingsScene>());
        game.launchGame(is::ecs::Scenes::SCENE_SPLASH_SCREEN);
    } catch (is::exceptions::Exception &e) {
        std::cerr << "CAUGHT EXCEPTION:" << std::endl;
        std::cerr << e.getComponent() << ": " << e.what() << std::endl;
        return 84;
    } catch (const std::exception &e) {
        std::cerr << "CAUGHT EXCEPTION:" << std::endl;
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    return (bomberman(argc, argv));
}
