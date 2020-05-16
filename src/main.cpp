/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Scenes/SplashScreenScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/SettingsScene.hpp"
#include "Scenes/ControllersScene.hpp"
#include "Scenes/CreditScene.hpp"
#include "Scenes/RecordScene.hpp"
#include "Scenes/HowToPlayScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Exception.hpp"

int main(int argc, char const *argv[])
{
    is::Game game;

    try {
        game.addScene(is::ecs::Scenes::SCENE_SPLASH_SCREEN, std::make_shared<is::scenes::SplashScreenScene>());
        game.addScene(is::ecs::Scenes::SCENE_MAIN_MENU, std::make_shared<is::scenes::MainMenuScene>());
        game.addScene(is::ecs::Scenes::SCENE_SETTINGS, std::make_shared<is::scenes::SettingsScene>());
        game.addScene(is::ecs::Scenes::SCENE_CONTROLLERS, std::make_shared<is::scenes::ControllersScene>());
        game.addScene(is::ecs::Scenes::SCENE_CREDIT, std::make_shared<is::scenes::CreditScene>());
        game.addScene(is::ecs::Scenes::SCENE_RECORD, std::make_shared<is::scenes::RecordScene>());
        game.addScene(is::ecs::Scenes::SCENE_HOWTOPLAY, std::make_shared<is::scenes::HowToPlayScene>());
        game.addScene(is::ecs::Scenes::SCENE_GAME, std::make_shared<is::scenes::GameScene>());
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
