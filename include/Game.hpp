/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include "ECS/IScene.hpp"

namespace is {

    class Game {
        public:
            Game() = default;
            ~Game() = default;

            Game(const Game &) = default;
            Game &operator=(const Game &) = default;

            enum Scenes {
                SCENE_SPLASH_SCREEN,
                SCENE_MAIN_MENU,
                SCENE_GAME
            };

            void addScene(Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene);
            void launchGame(Scenes startScene);

            static bool isRunning;

        protected:
        private:
            std::map<Scenes, std::shared_ptr<is::ecs::IScene>> _scenes;
            Scenes currentScene;
    };

}

#endif /* !GAME_HPP_ */
