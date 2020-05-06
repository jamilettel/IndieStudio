/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Scenes/GameScene.hpp"

int main(int argc, char const *argv[])
{
    is::Game game;

    try {
        game.addScene(is::Game::Scenes::SCENE_GAME, std::make_shared<is::scenes::GameScene>());
        game.launchGame(is::Game::Scenes::SCENE_GAME);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (1);
    }
    return (0);
}
