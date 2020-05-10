/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/SplashScreen.hpp"
#include "Exception.hpp"

int main(int argc, char const *argv[])
{
    is::Game game;

    try {
        game.addScene(is::ecs::Scenes::SCENE_SPLASH_SCREEN, std::make_shared<is::scenes::SplashScreenScene>());
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
