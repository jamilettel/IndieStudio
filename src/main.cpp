/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Scenes/SplashScreenScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/GameScene.hpp"

int main(int argc, char const *argv[])
{
    is::Game game;

    try {
        game.addScene(is::Game::Scenes::SCENE_SPLASH_SCREEN, std::make_shared<is::scenes::SplashScreenScene>());
        game.addScene(is::Game::Scenes::SCENE_MAIN_MENU, std::make_shared<is::scenes::MainMenuScene>());
        game.addScene(is::Game::Scenes::SCENE_GAME, std::make_shared<is::scenes::GameScene>());
        game.launchGame(is::Game::Scenes::SCENE_MAIN_MENU);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
