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

    game.addScene(is::Game::Scenes::SCENE_GAME, std::make_shared<GameScene>());
    game.launchGame(is::Game::Scenes::SCENE_GAME);
    return (0);
}
