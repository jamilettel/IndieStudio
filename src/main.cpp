/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include "Game.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/test.hpp"
#include "Exception.hpp"

int main(int argc, char const *argv[])
{
    is::Game game;

    try {
        game.addScene(is::ecs::Scenes::SCENE_GAME, std::make_shared<is::scenes::GameScene>());
        game.addScene(is::ecs::Scenes::NOTHING, std::make_shared<is::scenes::test>());
        game.launchGame(is::ecs::Scenes::SCENE_GAME);
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
